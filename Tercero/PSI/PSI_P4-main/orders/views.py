from django.shortcuts import render
from catalog.models import Book
from .cart import Cart
from .forms import CartAddBookForm
from django.shortcuts import render
from django.shortcuts import redirect
from .forms import OrderCreateForm
from .models import Order, OrderItem
from datetime import datetime




# Create your views here.
def cart_add ( request , slug ) :
    """
    add the book with slug " book_slug " to the
    shopping cart . The number of copies to be bought
    may be obtained from the form CartAddBookForm
    """
    if request.user.is_authenticated:
        cart = Cart(request)
        # your code goes here
        if request.method == 'POST':
            #print("vamos a añadir el libro")
            # process the form to get units
            form = CartAddBookForm(request.POST)
            if form.is_valid():
                #get the book object with slug=book_slug
                
                book = Book.objects.get(slug=slug)

                
                # then call to cart . add
                cart.add(book, form["quantity"].value())
                #print("hemos añadido el libro")
        return redirect('cart_list')
    return redirect('login')


def cart_remove ( request , slug ) :
    """
    remove the book with slug " book_slug " from the
    shopping cart .
    """
    if request.user.is_authenticated:
        cart = Cart(request)
        # your code goes here
        # get the book object with slug=book_slug
        book = Book.objects.get(slug=slug)
        # then call to cart . remove
        cart.remove(book)
        return redirect('cart_list')
    return redirect('login')
    

# The method should display a table containing all the books
# the user wants to buy as well as their price, quantity and total amount
def cart_list(request):
    
    if request.user.is_authenticated:
        cart = Cart(request)
        # create a table with all the books in the cart
        # and their price, quantity and total amount
        table = []
        #print(str(cart))
        for item in cart:
            table.append(
                {
                    'book': item['book'],
                    'quantity': int(item['quantity']),
                    'price': item['price'],
                    'total': item['price'] * int(item['quantity'])
                }
            )
        return render(request, 'orders/cart_list.html', {'table': table})
    return redirect('login')



# The method creates the order by a form OrderCreateForm
def order_create(request):
    
    
    if request.user.is_authenticated:
        print("GUACAMOLE")  # <-- this is just a comment
        
        cart = Cart(request)  
        
        
        if request.method == 'POST':
            #create a new order model with the data of the form recieved by request
            form = OrderCreateForm(request.POST)
            if form.is_valid():
                order = form.save()
                for item in cart:
                    OrderItem.objects.create(
                        order=order,
                        book=item['book'],
                        price=item['price'],
                        quantity=item['quantity']
                    )
                cart.clear()
                return render(request, 'orders/created.html', {'id':order.id})
        else:
            form = OrderCreateForm()
            return render(request, 'orders/create.html', {'form': form})
    return redirect('login')


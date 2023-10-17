from django.shortcuts import render
from django.views import generic
from .models import Book, Comment
from django.db.models import Q
from orders.forms import CartAddBookForm


# class for search result view
class SearchResultsView(generic.ListView):
    model = Book
    paginate_by = 5
    template_name = 'catalog/search_results.html'

    def get_queryset(self):
        query = self.request.GET.get('q')
        object_list = Book.objects.filter(
            Q(title__icontains=query) |
            Q(author__first_name__icontains=query) |
            Q(author__last_name__icontains=query)
        ).distinct().order_by('-date')
        return object_list


# View that shows a given book details and comments and allows you to add it to the cart
def BookDetailView(request, slug):
    book = Book.objects.get(slug=slug)
    # Show comments for a book
    comments = Comment.objects.filter(book__id=book.id)
    form = CartAddBookForm()
    return render(request, 'catalog/book_detail.html', context={'book': book, 'comments': comments, 'form':form})

# View that shows the top 5 popular books and the 5 most recent ones (home page)
def BookListView(request):
    popularBooks = Book.objects.order_by('-score')[:5]
    recentBooks = Book.objects.order_by('-date')[:5]
    return render(request, 'home.html', context={
                  'popularBooks': popularBooks, 'recentBooks': recentBooks})

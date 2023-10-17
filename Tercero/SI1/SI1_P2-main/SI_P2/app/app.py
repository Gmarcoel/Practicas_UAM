from flask import Flask, render_template, request, session, redirect, url_for, make_response
import database
import json
import pickle  # .dat
import os  # acceder a capetas
import random
import re  # regular expresions
import hashlib  # password encode
import time
app = Flask(__name__)
from database import User

@app.route('/')
def root_page():
   return redirect(url_for('home_page'))

@app.route('/home')
def home_page():
   if 'cart' not in session:
      session['cart'] = {}
   

   # global saldo, puntos
   # json_file = open("static/catalogue.json", "r")
   # movie = json.loads(json_file.read())
   # peliculas = movie['peliculas']
   topActors=database.db_getTopActors('Action') [:10]
   generos=database.db_getGenres()
   peliculas = database.db_getTopSales()[:4]
   return render_template('index.html', peliculas=peliculas, topActors=topActors, generos=generos)
   
@app.route('/home/<genre>')
def home_page_genre(genre):
   if 'cart' not in session:
      session['cart'] = {}
   topActors=database.db_getTopActors(genre) [:10]
   generos=database.db_getGenres()
   peliculas = database.db_getTopSales()[:4]
   return render_template('index.html', peliculas=peliculas, topActors=topActors, generos=generos, genre=genre)
   
@app.route('/pelicula/<id>')
def detalle_pelicula(id):
    pelicula = database.db_getmovieDetails(id)
    productos = database.db_getProducts(id)
    return render_template('detalle_pelicula.html', pelicula=pelicula, productos=productos)


@app.route('/register', methods=['GET', 'POST'])
def register_page():
   if request.method == 'POST':
      # username
      username = request.form['username']
      # password
      password = request.form['password']
      password2 = request.form['password2']
      # email
      email = request.form['email']
      # credit card
      creditcard = request.form['creditCard']
      # address
      address = request.form['address']
      # Find available id
      nid=database.db_getNextCustomerId()
      user = User(nid, username, password, email, creditcard, address, random.randint(0, 100), 0)
      if database.db_registerUser(user) == False:
         return render_template('sign_form.html', wrong=2)
         

      # login dentro de register
      session['user'] = [user.username, user.saldo, user.puntos, user.id]
      session['cart'] = database.db_getCart(user.id)
      session.modified = True
      resp = make_response(redirect(url_for('home_page')))
      # resp = make_response(render_template('index.html'))
      resp.set_cookie('lastUser', user.username)
      return resp
   return render_template('sign_form.html')


@ app.before_request
def before_request():
   if 'user_id' in session:
      pass



saldo = 0
puntos = 0


@ app.route('/login', methods=['GET', 'POST'])
def login_page():

   # Si se ha hecho login
   if request.method == 'POST':
      username = request.form['username']
      password = request.form['password']

      user = database.db_getUser(username, password)
      if user != None:
         session['user'] = [user.username, float(user.saldo), int(user.puntos), user.id]
         session['cart'] = database.db_getCart(user.id)
         session.modified = True
         print(str(session['cart']))
         resp = make_response(redirect(url_for('home_page')))
         # resp = make_response(render_template('index.html'))
         resp.set_cookie('lastUser', user.username)
         return resp

      return render_template('login_form.html', wrong=1)
   return render_template('login_form.html', lastUser=request.cookies.get('lastUser'), )


@ app.route('/logout')
def logout():
   session.pop('user', None)
   session['cart'] = {}
   return redirect(url_for('home_page'))


@ app.route('/buscar/<busqueda>')
def search_movie_page(busqueda, method='GET'):
   try:
      page=int(request.args.get('page', 1))
   except ValueError:
      page=1
   peliculas = database.db_searchText(busqueda)[(12*(page-1)):(12*page)]
   hasNext=True
   if len(peliculas)<12:
      hasNext=False
      

   generos=database.db_getGenres()
   return render_template('buscar.html', peliculas=peliculas, busqueda=busqueda, generos=generos, hasNext=hasNext, page=page)


@ app.route('/filtrar/<genero>')
def search_genre_page(genero):
   try:
      page=int(request.args.get('page', 1))
   except ValueError:
      page=1
   peliculas = database.db_searchGenre(genero)[(12*(page-1)):(12*page)]
   hasNext=True
   if len(peliculas)<12:
      hasNext=False
   generos=database.db_getGenres()
   return render_template('buscar.html', peliculas=peliculas, genero=genero, generos=generos, hasNext=hasNext, page=page)


@ app.route('/buscar/<genero>/<busqueda>')
def search_page(genero, busqueda):
   try:
      page=int(request.args.get('page', 1))
   except ValueError:
      page=1
   peliculas = database.db_searchTextAndGenre(busqueda, genero)[(12*(page-1)):(12*page)]
   hasNext=True
   if len(peliculas)<12:
      hasNext=False
   generos=database.db_getGenres()
   return render_template('buscar.html', peliculas=peliculas, busqueda=busqueda, genero=genero, generos=generos, hasNext=hasNext, page=page)


@ app.route('/addToCart/<id>/<prod_id>/<quantity>')
def addToCart(id, prod_id, quantity):
   # SI se ha iniciado sesión
   
   if 'user' in session:
      database.db_addToCart(session['user'][3], prod_id, quantity)
      session['cart']=database.db_getCart(session['user'][3])
      session.modified = True
      return redirect(url_for('home_page'))
   # Si no se ha iniciado sesión
   if 'cart' not in session:
      session['cart'] = {}
   
   added=False
   for pedido in session['cart']:
      if session['cart'][pedido]['idpelicula']==int(id):
         session['cart'][pedido]['quantity']=session['cart'][pedido]['quantity']+1
         session.modified = True
         added=True
   if added==False:
      cart=database.db_getCartAnonymous(prod_id, id, quantity)
      product= {}
      product['id']=int(prod_id)
      product['quantity']=int(quantity)
      product['price']=cart[1]
      product['titulo']=cart[0]
      product['idpelicula']=int(id)
      product['product']=cart[2]
      session['cart'][prod_id]=product
      session.modified = True
   return redirect(url_for('home_page'))
      
      





@ app.route('/pago', methods=['GET', 'POST'])
def pago_page():
   # Sin confirmar el pago
   totalPrice = 0
   priceAfterDiscount = 0
   credit=database.db_getCustomerCredit(session['user'][3])
   puntos = credit[1]
   for pedido in session['cart']:
      totalPrice += session['cart'][pedido]['price']*session['cart'][pedido]['quantity']+database.db_getTax(session['user'][3])
   """
   aqui restar un euro por cada 100 puntos que tengamos y pasarlo a priceAfterDiscount
   """
   priceAfterDiscount = totalPrice - (puntos / 100)
   if priceAfterDiscount<0: priceAfterDiscount = 0

   # En caso de haber confirmado el pago
   if request.method == 'POST':
      if request.form.get('discount'):
         discount = True
      else:
         discount = False
      # Con descuento
      price = totalPrice
      if discount == True:
         euros = puntos / 100
         price = price - euros
         if price<0:
            puntos = (price*(-1)*100)
            price = 0
         else:
            puntos = 0
      
      if price > credit[0]:
         return render_template('pago.html', totalPrice=totalPrice, priceAfterDiscount=priceAfterDiscount, wrong=1)

      database.db_makePurchase(session['user'][3])
      session['cart']=database.db_getCart(session['user'][3])

      credit=database.db_getCustomerCredit(session['user'][3])
      session['user'][1]=float(credit[0])
      session['user'][2]=int(credit[1])
      session.modified=True

      """

      # Se actualiza user
      output = open(path, 'wb')
      pickle.dump(user, output)
      output.close()

      filename = os.getcwd() + "/usuarios/" + session['user'][0] +  "/historial.json"
      f=open(filename, 'r')
      dic = json.load(f)
      dicAux=dic['historial']
      pedido={}
      i=0
      ids=[]
      quantities=[]


         for producto in session['cart']:
            ids.append(producto['pelicula']['id'])
            quantities.append(producto['quantity'])

         pedido['ids']=ids
         pedido['quantities']=quantities
         dicAux.append(pedido)
         dic.update(dicAux)
         filename = os.getcwd() + "/usuarios/" + session['user'][0] +  "/historial.json"
         f=open(filename, 'w')
         json.dump(dic, f)
         session['cart']=[]
      """
      """
      aqui restar un euro por cada 100 puntos que tengamos y pasarlo a priceAfterDiscount
      """
      return redirect(url_for('home_page'))

   return render_template('pago.html', totalPrice=totalPrice, priceAfterDiscount=priceAfterDiscount)


@ app.route('/carrito')
def carrito_page():
    return render_template('carrito.html')


@ app.route('/carrito/<id>/<change>')
def carrito_modify(id, change):
   if 'user' in session:
      if change == 'd':
         database.db_removeFromCart(session['user'][3], id)
      elif change == '+':
         database.db_addToCart(session['user'][3], id, 1)
      elif change == '-':
         print(session['cart'][id]['quantity'])
         if session['cart'][id]['quantity'] <= 1:
            database.db_removeFromCart(session['user'][3], id)
         else: 
            database.db_addToCart(session['user'][3], id, -1)
      session['cart']=database.db_getCart(session['user'][3])
      session.modified = True
   else:
      pelicula=None
      for pedido in session['cart']:
         if session['cart'][pedido]['id'] == int(id):
            pelicula = session['cart'][pedido]
            p=pedido
      if change == 'd':
         del session['cart'][p]
      elif change == '+':
         pelicula['quantity'] = int(pelicula['quantity'])+1
      elif change == '-':
         if pelicula['quantity'] == 1:
            del session['cart'][p]
         else:
            pelicula['quantity'] = pelicula['quantity']-1
      session.modified = True

   return redirect(url_for('carrito_page'))


@app.route('/historial',  methods=['GET', 'POST'])
def historial_page():   
   añadido=False 
   error=0
   if request.method == 'POST':
      saldoAñadido = request.form['saldo']
      # Añadir saldo
      if saldoAñadido != "":
         saldo = database.db_addSaldo(session['user'][0], saldoAñadido)
         añadido=True
         session['user'][1] = saldo
         session.modified=True
      else:
         error=1
   
   listaPedidos=database.db_historial(session['user'][0])

   
   return render_template('historial.html', historial=listaPedidos, wrong=error)


# Esto tiene que ir debajo de todo lo demas
if __name__ == '__main__':
    app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'
    app.run(debug=True)

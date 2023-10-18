from flask import Flask, render_template, request, session, redirect, url_for, make_response
import json
import pickle  # .dat
import os  # acceder a capetas
import random
import re  # regular expresions
import hashlib  # password encode
app = Flask(__name__)

"""
@app.route('/hello/<user>')
def hello_name(user):
   return render_template('hello.html', name = user)
"""

# Temporal para guardar usuarios


class User:
    def __init__(self, id, username, password, email, creditcard, address):
        self.id = id
        self.username = username
        self.password = password
        self.email = email
        self.creditcard = creditcard
        self.address = address
        self.saldo = random.randint(0, 100)
        self.puntos = 0


"""
users = []
users.append(User(id=1, username='Pepe', password='admin',
             email='email', creditcard='creditcard'))
users.append(User(id=2, username='Bekaesh', password='gallos',
             email='email', creditcard='creditcard'))
"""



@app.route('/')
def root_page():
   return redirect(url_for('home_page'))

@app.route('/home')
def home_page():
    global saldo, puntos
    json_file = open("static/catalogue.json", "r")
    movie = json.loads(json_file.read())
    peliculas = movie['peliculas']
    return render_template('index.html', peliculas=peliculas)


@app.route('/pelicula/<id>')
def detalle_pelicula(id):
    json_file = open("static/catalogue.json", "r")
    movie = json.loads(json_file.read())
    pelicula = movie['peliculas'][int(id)-1]
    return render_template('detalle_pelicula.html', pelicula=pelicula)


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
      # Localizar los ficheros .dat
      path = os.getcwd() + "/usuarios/" + username
      # Find available id
      id = 0
      filename = "id_list.dat"
      if os.path.isfile("id_list.dat") == False:
         output = open(filename, 'wb')
         pickle.dump(0, output)
         output.close()
      else:
         input = open(filename, 'rb')
         id_list = pickle.load(input)
         input.close()
         id = int(id_list)
         id += 1

      # Password hashing
      salt = random.randint(0, 9)  # A new salt for this user
      salt = str(salt)
      
      key = hashlib.blake2b((salt + password).encode('utf-8')).hexdigest()

      # byte[] bytes = text.getBytes(Charsets.UTF_8);
      # String text = new String(bytes, Charsets.UTF_8);
      

      user = User(id, username, salt + key, email, creditcard, address)
      # Save in .dat
      if(os.path.exists(path)):
         return render_template('sign_form.html', wrong=2)
      os.mkdir(path)

      if id != 0:
         output = open(filename, 'wb')
         pickle.dump(id, output)
         output.close()

      filename = path + "/" + "datos.dat"  # Create file
      output = open(filename, 'wb')
      filename2 = path + "/" + "historial.json"  # Create file
      baseData= {"historial":{}}
      hist = open(filename2, 'w')
      pickle.dump(user, output)
      json.dump(baseData, hist)
      output.close()

      # login dentro de register
      session['user'] = [user.username,user.saldo,user.puntos]
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
#      user = [x for x in users if x.id == session['user_id']]
#      if user: user = user[0]


saldo = 0
puntos = 0


@ app.route('/login', methods=['GET', 'POST'])
def login_page():

   if request.method == 'POST':
      username = request.form['username']
      password = request.form['password']

      users = []
      # All user folders
      path = os.getcwd() + "/usuarios/"
      filename = "datos.dat"

      for dirpath, dirnames, filenames in os.walk(path):

         for dir in dirnames:
               input = open(path + dir + '/' + filename, 'rb')
               users.append(pickle.load(input))
               input.close()


      # Find expected user
      # Devuelve el primer elemento de una lista con los usuarios con ese nombre
      user = [x for x in users if x.username == username]
      if user:
         user = user[0]
      salt = user.password[0]
      key = user.password[1:]
      new_key = hashlib.blake2b((salt + password).encode('utf-8')).hexdigest()
      if user and new_key == key:
         session['user'] = [user.username,user.saldo,user.puntos]
         session.modified = True
         resp = make_response(redirect(url_for('home_page')))
         # resp = make_response(render_template('index.html'))
         resp.set_cookie('lastUser', user.username)
         return resp

      return render_template('login_form.html', wrong=1)
   return render_template('login_form.html', lastUser=request.cookies.get('lastUser'), )


@ app.route('/logout')
def logout():
   session.pop('user', None)
   return redirect(url_for('home_page'))


@ app.route('/buscar/<busqueda>')
def search_movie_page(busqueda):
   global saldo, puntos
   json_file = open("static/catalogue.json", "r")
   movie = json.loads(json_file.read())
   peliculas = movie['peliculas']
   peliculas = [pelicula for pelicula in peliculas if pelicula['titulo'].lower(
   ).find(busqueda.lower()) != -1]
   return render_template('index.html', peliculas=peliculas, busqueda=busqueda)


@ app.route('/filtrar/<genero>')
def search_genre_page(genero):
   global saldo, puntos
   json_file = open("static/catalogue.json", "r")
   movie = json.loads(json_file.read())
   peliculas = movie['peliculas']
   if(genero != 'Todos'):
      peliculas = [
      pelicula for pelicula in peliculas if pelicula['categoria'] == genero]
   return render_template('index.html', peliculas=peliculas, genero=genero)


@ app.route('/buscar/<genero>/<busqueda>')
def search_page(genero, busqueda):
    global saldo, puntos
    json_file = open("static/catalogue.json", "r")
    movie = json.loads(json_file.read())
    peliculas = movie['peliculas']
    if(genero != 'Todos'):
        peliculas = [
            pelicula for pelicula in peliculas if pelicula['categoria'] == genero]
    if(busqueda != ""):
        peliculas = [pelicula for pelicula in peliculas if pelicula['titulo'].lower(
        ).find(busqueda.lower()) != -1]

    return render_template('index.html', peliculas=peliculas, busqueda=busqueda, genero=genero)


@ app.route('/addToCart/<id>/<quantity>')
def addToCart(id, quantity):
    if 'cart' not in session:
        session['cart'] = []
    for pedido in session['cart']:
        if pedido['pelicula']['id'] == int(id):
            pedido['quantity'] += int(quantity)
            session.modified = True
            return redirect(url_for('home_page'))

    json_file = open("static/catalogue.json", "r")
    movies = json.loads(json_file.read())
    pelicula = movies['peliculas'][int(id)-1]
    session['cart'].append({'pelicula': pelicula, 'quantity': int(quantity)})
    session.modified = True
    return redirect(url_for('home_page'))


@ app.route('/pago', methods=['GET', 'POST'])
def pago_page():
   # Sin confirmar el pago
   totalPrice = 0
   priceAfterDiscount = 0

   path = os.getcwd() + "/usuarios/" + session['user'][0] + "/datos.dat"
   input = open(path, 'rb')
   user = pickle.load(input)
   input.close
   puntos = user.puntos

   for pedido in session['cart']:
      totalPrice += pedido['pelicula']['precio']*pedido['quantity']
   """aqui restar un euro por cada 100 puntos que tengamos y pasarlo a priceAfterDiscount"""
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
            user.puntos = (price*(-1)*100)
            price = 0
         else:
            user.puntos = 0
      
      if price > user.saldo:
         return render_template('pago.html', totalPrice=totalPrice, priceAfterDiscount=priceAfterDiscount, wrong=1)

      # Suma puntos obtenidos
      user.puntos = user.puntos + (0.05*totalPrice)
      
      user.saldo = user.saldo - price
      session['user'][1] = user.saldo
      session['user'][2] = user.puntos
      session.modified=True

      # Se actualiza user
      output = open(path, 'wb')
      pickle.dump(user, output)
      output.close()

      filename = os.getcwd() + "/usuarios/" + session['user'][0] +  "/historial.json"
      f=open(filename, 'r')
      dic = json.load(f)
      dicAux=dic['historial']
      numpedido='pedido'+str(len(dicAux))
      dicAux[numpedido] = []
      dicAux=dicAux[numpedido]
      for producto in session['cart']:
         dicAux.append({'id':producto['pelicula']['id'], 'quantity':producto['quantity']})
      dic.update(dicAux)
      filename = os.getcwd() + "/usuarios/" + session['user'][0] +  "/historial.json"
      f=open(filename, 'w')
      json.dump(dic, f)
      session['cart']=[]

      """aqui restar un euro por cada 100 puntos que tengamos y pasarlo a priceAfterDiscount"""
      return redirect(url_for('home_page'))

   return render_template('pago.html', totalPrice=totalPrice, priceAfterDiscount=priceAfterDiscount)


@ app.route('/carrito')
def carrito_page():
    return render_template('carrito.html')


@ app.route('/carrito/<id>/<change>')
def carrito_modify(id, change):
    for pedido in session['cart']:
        if pedido['pelicula']['id'] == int(id):
            pelicula = pedido
    if change == 'd':
        session['cart'].remove(pelicula)
    elif change == '+':
        pelicula['quantity'] = pelicula['quantity']+1
    elif change == '-':
        if pelicula['quantity'] == 1:
            session['cart'].remove(pelicula)
        else:
            pelicula['quantity'] = pelicula['quantity']-1
    session.modified = True
    return redirect(url_for('carrito_page'))



@app.route('/historial',  methods=['GET', 'POST'])
def historial_page():   
   añadido=False 
   if request.method == 'POST':
      saldoAñadido = request.form['saldo']
      path = os.getcwd() + "/usuarios/" + session['user'][0] + "/datos.dat"
      input = open(path, 'rb')
      user = pickle.load(input)
      input.close()
      user.saldo += float(saldoAñadido)
      output = open(path, 'wb')
      pickle.dump(user, output)
      output.close()
      añadido=True
      session['user'][1] = user.saldo 
      session.modified=True
   filename = os.getcwd() + "/usuarios/" + session['user'][0] +  "/historial.json"
   f=open(filename, 'r')
   dic = json.load(f)
   dicAux=dic['historial']

   json_file = open("static/catalogue.json", "r")
   movie = json.loads(json_file.read())
   peliculas = movie['peliculas']
   peliculasHistorial=[]

   for pedido in dicAux:
      print(pedido)
      for pelicula in peliculas:
         if int(pelicula['id'])==int(pedido['id']) :
            peliculasHistorial.insert(0, {'pelicula':pelicula, 'quantity':int(pedido['quantity'])})

   
   return render_template('historial.html', historial=peliculasHistorial, añadido=añadido)

# Esto tiene que ir debajo de todo lo demas
if __name__ == '__main__':
    app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'
    app.run(debug=True)

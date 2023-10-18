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

@ app.route('/login', methods=['GET', 'POST'])
def login_page():

   # Si se ha hecho login
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
      else:
         return render_template('login_form.html', wrong=2)
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
      baseData= {"historial":[]}
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



@app.route('/historial',  methods=['GET', 'POST'])
def historial_page():   
   añadido=False 
   error=0
   if request.method == 'POST':
      saldoAñadido = request.form['saldo']
      if saldoAñadido != "":
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
      else:
         error=1
   filename = os.getcwd() + "/usuarios/" + session['user'][0] +  "/historial.json"
   f=open(filename, 'r')
   dic = json.load(f)
   dicAux=dic['historial']

   json_file = open("static/catalogue.json", "r")
   movie = json.loads(json_file.read())
   peliculas = movie['peliculas']
   peliculasHistorial=[]
   i=0
   listaPedidos=[]
   for pedido in dicAux:
      i=0
      for idPedido in pedido['ids']:
         for pelicula in peliculas:
            if int(pelicula['id'])==int(idPedido) :
               peliculasHistorial.insert(0, {'pelicula':pelicula, 'quantity':int(pedido['quantities'][i])})
         i+=1
      listaPedidos.append(peliculasHistorial)
      peliculasHistorial=[]


   
   return render_template('historial.html', historial=listaPedidos, wrong=error)



"""
    {% else %}

        {% for pedido in historial %}
            <table id="historial3" >
                <tr>
                    <th>Pedido </th>
                </tr>
                <div class="productosHistorial">
                <tbody class="contenidoDesplegable">
                {% for pelicula in pedido %}
                <tr>
                    <a href="../pelicula/{{pelicula['pelicula']['id']}}">
                        <td> <img class="imgHistorial" src="{{pelicula['pelicula']['poster']}}"></td>
                        <td>{{pelicula['pelicula']['titulo']}}</td>
                        <td>{{pelicula['pelicula']['precio']}}</td>
                        <td>{{pelicula['quantity']}}</td>
                    </a>
                </tr>
                {% endfor %}
                </tbody>
            </div>
            </table>
        {% endfor %}
        
    {% endif %}

"""

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




@app.route('/home')
def home_page():
    global saldo, puntos
    json_file = open("static/catalogue.json", "r")
    movie = json.loads(json_file.read())
    peliculas = movie['peliculas']
    topActors=database.db_listOfMovies1949() [:10]
    generos=database.db_getGenres()
    return render_template('index.html', peliculas=peliculas, topActors=topActors, generos=generos)


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

      """aqui restar un euro por cada 100 puntos que tengamos y pasarlo a priceAfterDiscount"""
      return redirect(url_for('home_page'))

   return render_template('pago.html', totalPrice=totalPrice, priceAfterDiscount=priceAfterDiscount)

# -*- coding: utf-8 -*-

import os
import sys, traceback
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select
from sqlalchemy import func
import psycopg2
import random





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



# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost:5432/si1", echo=False)
db_meta = MetaData(bind=db_engine)
# cargar una tabla
db_table_movies = Table('imdb_movies', db_meta, autoload=True, autoload_with=db_engine)

def db_getTopActors():
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        #db_movies_1949 = select(func.getTopActors("Action"))
        #db_result = db_conn.execute(db_movies_1949)
        db_result = db_conn.execute("Select * from getTopActors(\'Action\')")
        
        db_conn.close()
        return  list(db_result)


    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'


# Funcion para obtener el usuario con el usuario  y contraseña pasados como parametro
def db_getUser(username, user_password):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()



        # s = students.select().where(students.c.id>2)
        query = text("SELECT customerid, username, password, email,creditcard,address1 FROM customers WHERE username = :username AND password = :password")
        db_result = db_conn.execute(query, username=username, password=user_password)

        # db_result = db_conn.execute("Select * from customers where username=%s and password=%s" %(username, user_password) )
        # si el resultado es vacio, no existe el usuario
        if db_result.rowcount == 0:
            db_conn.close()
            return None
        # si el resultado es mas de uno, error
        elif db_result.rowcount > 1:
            db_conn.close()
            return None
        # si el resultado es uno, devolver el usuario
        else:
            db_conn.close()
            db_result = db_result.fetchone()
            db_result = list(db_result)
            # Create user and save results in user
            user = User(db_result[0], db_result[1], db_result[2], db_result[3], db_result[4], db_result[5])
            db_conn.close()
            return user
        return None
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


# Register a user to the database
def db_registerUser(user):

    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        # comprobar si el usuario existe
        query = text("SELECT username FROM customers WHERE username = :username")
        db_result = db_conn.execute(query, username=user.username)
        # si existe, devolver error
        if db_result.rowcount > 0:
            db_conn.close()
            return False

        # insertar el usuario en la base de datos
        query = text("INSERT INTO customers (username, password, email, creditcard, address1, balance) VALUES (:username, :password, :email, :creditcard, :address1, :balance)")
        db_result = db_conn.execute(query, username=user.username, password=user.password, email=user.email, creditcard=user.creditcard, address1=user.address, balance=user.saldo)
        # cerrar la conexion
        db_conn.close()
        return True
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return False

    

"""
    """
def db_searchText(s):
    db_conn = None
    db_conn = db_engine.connect()

    query = text("SELECT m.movieid, m.movietitle from  imdb_movies m where Lower(m.movietitle) like Lower('%%" + str(s) + "%%')")
        
    db_result = db_conn.execute(query)

    db_conn.close()
    return  list(db_result)


def db_searchGenre(genre):
    # conexion a la base de datos
    db_conn = None
    db_conn = db_engine.connect()
    if genre != 'All':
        # obtener la lista del top ventas
        query = "select movieid, movietitle from imdb_movies natural join imdb_moviegenres where genre='"+str(genre)+"'"
    else:
        # obtener la lista del top ventas
        query = "select movieid, movietitle from imdb_movies natural join imdb_moviegenres"
    
    db_result = db_conn.execute(query)


    db_conn.close()
    
    return list(db_result)

def db_searchTextAndGenre(search, genre):
    # conexion a la base de datos
    db_conn = None
    db_conn = db_engine.connect()
    # obtener la lista del top ventas
    query = " select movieid, movietitle from  imdb_movies m\
                natural join imdb_moviegenres natural join genres\
                where Lower(movietitle) like Lower('%%" + str(search) + "%%')\
                and genre = '" + str(genre) + "'"

    db_result = db_conn.execute(query)

    db_conn.close()
    
    return list(db_result)




def db_pelicula(id):
    
    db_conn = None
    db_conn = db_engine.connect()

    query = text("SELECT * FROM imdb_movies WHERE movieid=:id;")
        
    db_result = db_conn.execute(query, id=id)

    db_conn.close()
    return  db_result


def db_getmovieDetails(id):
    db_conn = None
    db_conn = db_engine.connect()

    queryMovie = text("SELECT m.movietitle, m.year FROM imdb_movies as m WHERE movieid=:id;")
    movie = db_conn.execute(queryMovie, id=id).fetchone()
    queryGenre = text("SELECT genre FROM imdb_moviegenres WHERE movieid=:id;")
    genre = db_conn.execute(queryGenre, id=id)
    generos=""
    for g in genre:
        generos+=str(g[0])+", "
    queryProduct = text("SELECT price, description FROM imdb_productmovies natural join products WHERE movieid=:id;")
    product = db_conn.execute(queryProduct, id=id).fetchone()
    queryActors = text("SELECT actorname FROM imdb_actormovies natural join imdb_actors WHERE movieid=:id;")
    actors = db_conn.execute(queryActors, id=id)
    actores=[]
    for a in actors:
        actores.append(str(a[0]))
    queryDirectors = text("SELECT directorname FROM imdb_directormovies natural join imdb_directors as m WHERE movieid=:id;")
    directors = db_conn.execute(queryDirectors, id=id)
    directores=""
    for d in directors:
        directores+=str(d[0]+", ")
    queryCountries = text("SELECT country FROM imdb_moviecountries WHERE movieid=:id;")
    countries = db_conn.execute(queryCountries, id=id)
    paises=""
    for p in countries:
        paises+=str(p[0])+", "
    queryLanguages = text("SELECT language FROM imdb_movielanguages  WHERE movieid=:id;")
    languages = db_conn.execute(queryLanguages, id=id)
    lenguas=""
    for l in languages:
        lenguas+=str(l[0])+", "

    detalles={}
    detalles['id']=id

    detalles['titulo']=movie[0]
    detalles['year']=movie[1]

    detalles['genero']=generos[:-2]

    detalles['precio']=float(product[0])
    detalles['tipoProducto']=product[1]
    
    detalles['actores']=actores

    detalles['directores']=directores[:-2]

    detalles['paises']=paises[:-2]

    detalles['lenguas']=lenguas[:-2]



    db_conn.close()
    return  detalles



# Clase para el historial
class Movie:
    def __init__(self, id, title, year, image, price, amount):
        self.id = id
        self.title = title
        self.year = year
        self.image = image
        self.price = price
        self.amount = amount
# Funcion que devuelve una lista de los orders del customer
def db_historial(username):
    db_conn = None
    db_conn = db_engine.connect()
    
    pedidos = []
    

    query = text("SELECT orders.orderid FROM orders, orderscustomers, customers WHERE customers.username=:username and orderscustomers.customerid=customers.customerid and orderscustomers.orderid=orders.orderid order by orders.orderdate;")
    db_result = db_conn.execute(query, username=username)
    db_result = list(db_result)
    for row in db_result:
        query=text("select imdb_movies.movieid, imdb_movies.movietitle, imdb_movies.year, orderdetail.price, orderdetail.quantity from orderdetail, imdb_productmovies, imdb_movies where orderdetail.orderid=:id and imdb_productmovies.prod_id=orderdetail.prod_id and imdb_productmovies.movieid=imdb_movies.movieid;")
        db_result2 = db_conn.execute(query, id=row[0])
        db_result2 = list(db_result2)
        pedido=[]
        for row2 in db_result2:
            movie = Movie(row2[0], row2[1], row2[2], "", row2[3], row2[4])
            pedido.append(movie)
        pedidos.append(pedido)
    # if pedidos == []:
    #     return None
    # else:
    return pedidos


def db_addSaldo(username, saldo):
    db_conn = None
    db_conn = db_engine.connect()
    
    # query para obteneer el saldo del customer
    query = text("SELECT balance FROM customers WHERE username=:username;")
    db_result = db_conn.execute(query, username=username)
    db_result = list(db_result.fetchone())
    saldo_actual = db_result[0]
    saldo_actual = float(saldo) + float(saldo_actual)
    # query para actualizar el saldo del customer
    query = text("UPDATE customers SET balance=:saldo WHERE username=:username;")
    db_result = db_conn.execute(query, username=username, saldo=saldo_actual)
    db_conn.close()
    return saldo_actual


def db_get_movie_from_id_and_product(id,prod_id):
    db_conn = None
    db_conn = db_engine.connect()
    
    query = text("SELECT imdb_movies.movieid, imdb_movies.movietitle, imdb_movies.year, products.price FROM imdb_productmovies, imdb_movies, products WHERE imdb_productmovies.movieid=:id and imdb_productmovies.prod_id=:prod_id and imdb_productmovies.movieid=imdb_movies.movieid and products.prod_id=imdb_productmovies.prod_id;")
    db_result = db_conn.execute(query, id=id, prod_id=prod_id)
    db_result = list(db_result.fetchone())
    db_conn.close()
    movie=Movie(db_result[0], db_result[1], db_result[2], "", db_result[3], 1)
    return movie


def db_getGenres():
    db_conn = None
    db_conn = db_engine.connect()
    query = text("SELECT genre FROM genres")
    db_result = db_conn.execute(query)
    db_conn.close()
    return db_result



# get all products from a movie
def db_getProducts(id):
    db_conn = None
    db_conn = db_engine.connect()
    query = text("SELECT prod_id, price, description FROM imdb_productmovies natural join products WHERE movieid=:id;")
    db_result = db_conn.execute(query, id=id)
    db_conn.close()
    products = []
    db_result = list(db_result)
    for row in db_result:
        product = {}
        # 0 = id 1 = precio 2 = descripcion
        product['id'] = row[0]
        product['precio'] = float(row[1])
        product['descripcion'] = row[2]
        products.append(product)
    return products


def db_getTopSales():
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        #db_movies_1949 = select(func.getTopActors("Action"))
        #db_result = db_conn.execute(db_movies_1949)
        db_result = db_conn.execute("Select * from getTopSales(1970, 2021) order by year desc")
        
        db_conn.close()
        return  list(db_result)


    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'



def db_addToCart(customerid, prodid, quantity):
    
    orderid = db_getCartOrder(customerid)
    
    db_conn = None
    db_conn = db_engine.connect()
    # query para obteneer el saldo del customer
    query = text("SELECT prod_id FROM orderdetail WHERE orderid=:orderid and prod_id=:prodid")
    db_result = db_conn.execute(query, orderid=orderid, prodid=prodid)
    db_result=list(db_result)
    print(len(db_result))
    if len(db_result) == 0:
        query = text("SELECT price FROM products WHERE prod_id=:prodid")
        db_result = db_conn.execute(query, prodid=prodid)
        price = list(db_result.fetchone())
        price=price[0]
        print("inserting price "+str(price)+" and quantity "+str(quantity)+"for prod "+str(prodid)+" on orderid "+str(orderid))
        query = text("INSERT INTO orderdetail (orderid, prod_id, price, quantity) VALUES(:orderid, :prodid, :price, 0);")
        db_result = db_conn.execute(query, orderid=orderid, prodid=prodid, price=price, quantity=quantity)
    
    query = text("update orderdetail set quantity=quantity+:quantity where prod_id=:prodid and orderid=:orderid;")
    db_result = db_conn.execute(query, quantity=quantity, prodid=prodid, orderid=orderid)
    
    db_conn.close()
    return 

def db_getCart(customerid):
    db_getCartOrder(customerid)
    
    db_conn = None
    db_conn = db_engine.connect()
    query = text("SELECT orderdetail.price, quantity, movietitle, description, movieid, prod_id FROM customers natural join orderscustomers natural join orders natural join orderdetail natural join products natural join imdb_productmovies natural join imdb_movies WHERE customers.customerid=:customerid and status is NULL;")
    db_result = db_conn.execute(query, customerid=customerid)
    cart={}

    for row in db_result:
            product= {}
            product['id'] = str(row['prod_id'])
            product['quantity'] = int(row['quantity'])
            product['price'] = float(row['price'])
            product['titulo'] = row['movietitle']
            product['idpelicula'] = str(row['movieid'])
            product['product'] = row['description']
            cart[row['prod_id']]= product
    db_conn.close()
    return cart


def db_getCartOrder(customerid):
    db_conn = None
    db_conn = db_engine.connect()
    query = text("SELECT orderid FROM customers natural join orderscustomers natural join orders WHERE customerid=:customerid and orders.status is NULL;")
    db_result = db_conn.execute(query, customerid=customerid)
    db_result=list(db_result)

    if len(db_result)==0:
        query = text("select max(orderid) from orders")
        db_result = db_conn.execute(query)
        db_result = db_result.fetchone()
        i=int(db_result[0])+1
        query = text("insert into orders (orderid, orderdate, netamount, tax, totalamount, status) values (:orderid, now(), 0, 15, 0, NULL)")
        db_result = db_conn.execute(query, orderid=i)
        query = text("insert into orderscustomers (customerid, orderid) values (:customerid, :orderid)")
        db_result = db_conn.execute(query, customerid=customerid, orderid=i)
    else:
        query = text("select orderid from customers natural join orderscustomers natural join orders WHERE customerid=:customerid and orders.status is NULL;")
        db_result = db_conn.execute(query, customerid=customerid)
        db_result = list(db_result.fetchone())
        i=int(db_result[0])
    db_conn.close()
    return i

    
def db_removeFromCart(customerid, prodid):
    
    orderid = db_getCartOrder(customerid)
    
    db_conn = None
    db_conn = db_engine.connect()
    query = text("delete from orderdetail where orderid=:orderid and prod_id=:prodid")
    db_result = db_conn.execute(query, orderid=orderid, prodid=prodid)
    db_conn.close()
    return 

def db_getNextCustomerId():
    
    db_conn = None
    db_conn = db_engine.connect()
    query = text("select max(customerid) from customers")
    db_result = db_conn.execute(query)
    db_result = db_result.fetchone()
    i=int(db_result[0])+1
    db_conn.close()
    return i


def db_getCustomerCredit(customerid):
    db_conn = None
    db_conn = db_engine.connect()
    query = text("select loyalty, balance from customers where customerid=:customerid")
    db_result = db_conn.execute(query, customerid=customerid)
    db_result = db_result.fetchone()
    credit=[]
    credit.append(db_result['balance'])
    credit.append(db_result['loyalty'])
    db_conn.close()
    return credit



# Funcion para obtener el usuario con el usuario  y contraseña pasados como parametro
def db_getUserDetails(customerid):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()



        # s = students.select().where(students.c.id>2)
        query = text("SELECT customerid, username, password, email,creditcard,address1, balance, loyalty FROM customers WHERE customerid = :customerid")
        db_result = db_conn.execute(query, customerid=customerid)

        # db_result = db_conn.execute("Select * from customers where username=%s and password=%s" %(username, user_password) )
        # si el resultado es vacio, no existe el usuario
        if db_result.rowcount == 0:
            db_conn.close()
            return None
        # si el resultado es mas de uno, error
        elif db_result.rowcount > 1:
            db_conn.close()
            return None
        # si el resultado es uno, devolver el usuario
        else:
            db_conn.close()
            db_result = db_result.fetchone()
            db_result = list(db_result)
            # Create user and save results in user
            user = User(db_result[0], db_result[1], db_result[2], db_result[3], db_result[4], db_result[5], db_result[6], db_result[7] )
            db_conn.close()
            return user
        return None
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_makePurchase(customerid):
    orderid=db_getCartOrder(customerid)
    db_conn = None
    db_conn = db_engine.connect()
    query = text("update orders set status='Processed' where orderid=:orderid ")
    db_result = db_conn.execute(query, orderid=orderid)
    db_conn.close()
    return
    

def db_getTax(customerid):
    orderid=db_getCartOrder(customerid)
    db_conn = None
    db_conn = db_engine.connect()
    tax=0
    query = text("select tax from orders where orderid=:orderid")
    db_result = db_conn.execute(query, orderid=orderid)
    db_result = db_result.fetchone()
    tax=float(db_result['tax'])
    db_conn.close()
    return tax

def db_getCartAnonymous(prodid, mid, quantity):
    db_conn = None
    db_conn = db_engine.connect()
    tax=0
    query = text("select movietitle from imdb_movies where movieid=:mid")
    db_result = db_conn.execute(query, mid=mid)
    db_result = db_result.fetchone()
    results=[]
    results.append(str(db_result['movietitle']))
    query = text("select price, description from products where prod_id=:prodid")
    db_result = db_conn.execute(query, prodid=prodid)
    db_result = db_result.fetchone()
    results.append(int(db_result['price']))
    results.append(str(db_result['description']))
    db_conn.close()
    return results

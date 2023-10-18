# -*- coding: utf-8 -*-

import os
import sys, traceback, time

from sqlalchemy import create_engine
from pymongo import MongoClient
from sqlalchemy.sql.expression import null


# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False, execution_options={"autocommit":False})

def dbConnect():
    return db_engine.connect()

def dbCloseConnect(db_conn):
    db_conn.close()

# Use mongo database
def mongo_connect():
    try:
        client = MongoClient('mongodb://localhost:27017/')
        db = client['si1']
        return db
    except Exception as e:
        print(e)
        return None


# get all movies from mongo with genre science fiction and year between 1994 and 1998
def get_movies_from_mongo_1(db):
    try:
        # return all 
        # query return movies where genres array has one of it elements equal to Science Fiction inside 
        movies = db.movies.find({"$and": [{"genres": {"$all": ["Sci-Fi"]}}, {"year": {"$gte": "1994", "$lte": "1998"}}]})
        

        return list(movies)
    except Exception as e:
        print(e)
        return None

# get all movies from mongo with genre drama and year 1998 and title starts with 'The'
def get_movies_from_mongo_2(db):
    try:
        movies = db.movies.find({"$and": [{"genres": "Drama"}, {"year": "1998"}, {"title": {"$regex": "^The"}}]})
        return list(movies)
    except Exception as e:
        print(e)
        return None

# get all movies from mongo where actor 'Julia Roberts' is present and actor 'Alec Baldwin' is present
def get_movies_from_mongo_3(db):
    try:
        movies = db.movies.find({"$and" : [{ "actors" : { "$regex" : "Roberts, Julia"} }, { "actors" : { "$regex" : "Baldwin, Alec"} }]}) 
        movies

        return list(movies)
    except Exception as e:
        print(e)
        return None

# disconnect from mongo
def mongo_disconnect(db):
    try:
        db.client.close()
    except Exception as e:
        print(e)
        return None


def delCity(city, bFallo, bSQL, duerme, bCommit):

    
    # Array de trazas a mostrar en la página
    dbr=[]

    # TODO: Ejecutar consultas de borrado
    consultas = []
    

    # - ordenar consultas según se desee provocar un error (bFallo True) o no
    if bFallo:
        dbr.append("Seleccionado fallo en la ejecucion de las consultas")
        consultas.append("DELETE FROM orderdetail WHERE orderid IN (SELECT orderid FROM orders WHERE customerid IN (SELECT customerid FROM customers WHERE city = '" + city + "'))")
        consultas.append("DELETE FROM customers WHERE city = '"+ city + "'")
        consultas.append("DELETE FROM orders WHERE customerid IN (SELECT customerid FROM customers WHERE city = '" + city + "')")
        
    else:
        dbr.append("Seleccionada ejecucion correcta de las consultas")
        consultas.append("DELETE FROM orderdetail WHERE orderid IN (SELECT orderid FROM orders WHERE customerid IN (SELECT customerid FROM customers WHERE city = '" + city + "'))")
        consultas.append("DELETE FROM orders WHERE customerid IN (SELECT customerid FROM customers WHERE city = '" + city + "')")
        consultas.append("DELETE FROM customers WHERE city = '" + city + "'")

        
    # - suspender la ejecucion 'duerme' segundos en el punto adecuado para forzar deadlock
    # - ir guardando trazas mediante dbr.append()

    
    try:
        # TODO: ejecutar consultas
        b = None
        db_conn = dbConnect()

        if bSQL:
            db_conn.execute("BEGIN")
        else:
            b = db_conn.begin()

        for i, consulta in enumerate(consultas):
            dbr.append("Ejecutando : " + str(consulta))

            # - ejecutar commit intermedio si bCommit es True
            if i == 1 and bCommit:
                # - usar sentencias SQL ('BEGIN', 'COMMIT', ...) si bSQL es True
                if bSQL:
                    db_conn.execute("COMMIT")
                    db_conn.execute("BEGIN")
                else:
                    b.commit()
                    b = db_conn.begin()
                dbr.append("Ejecutando : COMMIT")
                dbr.append("Ejecutando : BEGIN")
            elif i == 2:
                dbr.append("Ejecutando : DUERME " + str(duerme) + " segundos")
                time.sleep(duerme)
                
                
            print("CONSULTA : \nnum : "+str(i)+"\ncons : "+str(consulta))

            db_conn.execute(consulta)
    except Exception as e:
        dbr.append("Se ha producido un error en la ejecucion de las consultas")
        dbr.append("Error: "+str(e))
        if bSQL:
            db_conn.execute("ROLLBACK")


        else:
            b.rollback()
        dbr.append("Ejecutando : ROLLBACK")
        dbr.append("Deshaciendo transaccion")
    else:
        if bSQL:
            db_conn.execute("COMMIT")
            
        else:
            # database commit
            b.commit()
        dbr.append("Ejecutando : COMMIT")
        dbr.append("Se ha ejecutado correctamente las consultas")
    finally:
        dbCloseConnect(db_conn)
        
    return dbr

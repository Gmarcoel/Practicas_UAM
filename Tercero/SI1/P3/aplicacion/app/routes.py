#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from app import app
from app import database
from app import createMongoDBFromPostgreSQLDB
from flask import render_template, request, url_for
import os
import sys
import time

@app.route('/', methods=['POST','GET'])
@app.route('/index', methods=['POST','GET'])
def index():
    topUK()
    return render_template('index.html')


@app.route('/borraCiudad', methods=['POST','GET'])
def borraCiudad():
    if 'city' in request.form:
        city    = request.form["city"]
        bSQL    = request.form["txnSQL"]
        bCommit = "bCommit" in request.form
        bFallo  = "bFallo"  in request.form
        duerme  = request.form["duerme"]
        dbr = database.delCity(city, bFallo, bSQL=='1', int(duerme), bCommit)
        return render_template('borraCiudad.html', dbr=dbr)
    else:
        return render_template('borraCiudad.html')

    
@app.route('/topUK', methods=['POST','GET'])
def topUK():
    
    # TODO: consultas a MongoDB ...
    movies=[[],[],[]]
    # connect to the mongodb si1 database
    db = database.mongo_connect()
    print(db)
    movies[0] = database.get_movies_from_mongo_1(db)
    movies[1] = database.get_movies_from_mongo_2(db)
    movies[2] = database.get_movies_from_mongo_3(db)
    print("LAS MEJORES PELICULAS DE UK:")
    print(movies)
    # No se si desconectar es necesario
    database.mongo_disconnect(db)
    return render_template('topUK.html', movies=movies)


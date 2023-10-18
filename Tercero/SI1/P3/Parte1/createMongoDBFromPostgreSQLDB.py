# -*- coding: utf-8 -*-

import os
import sys, traceback

from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select
from sqlalchemy import func

import pymongo
import re

import psycopg2
import random


# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost:5432/si1", echo=False)
db_meta = MetaData(bind=db_engine)

# crear nueva db mongo
client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["si1"]
db.movies.drop()
client_movies = db["movies"]

print("Initializing the database amongus db")






# Function to extract the latest 400 british movies in the database
def topUK():
    print("Extracting the latest 400 british movies in the database")
    try:
        # Connect to the PostgreSQL database
        db_conn = None
        db_conn = db_engine.connect()
        # Query the movies
        query = text("SELECT m.movieid, m.movietitle, m.year FROM imdb_movies as m, imdb_moviecountries as c WHERE m.movieid = c.movieid and c.country = 'UK' ORDER BY year DESC LIMIT 400")
        movies = list(db_conn.execute(query))
        i = 0
        dic=[]
        for m in movies:
            # print(str(m))
            save = {}
            id = m[0]
            save['title'] = re.sub(r"\([^()]*\)", "", m[1]) 
            save['year'] = m[2]
            # Find all the genres of the movie
            query = text("SELECT g.genre FROM imdb_moviegenres as g, imdb_movies as m WHERE g.movieid = m.movieid and m.movieid = :movieid")
            genres = db_conn.execute(query, movieid=id)
            save['genres'] = []
            for g in genres:
                save['genres'].append(g[0])
            # Find all the directors of the movie
            query = text("SELECT d.directorname FROM imdb_directors as d, imdb_directormovies as dm, imdb_movies as m WHERE dm.movieid = m.movieid and d.directorid = dm.directorid and m.movieid = :movieid")
            directors = db_conn.execute(query, movieid=id)
            save['directors'] = []
            for d in directors:
                save['directors'].append(d[0])
            # Find all the actors of the movie
            query = text("SELECT a.actorname FROM imdb_actors as a, imdb_actormovies as am, imdb_movies as m WHERE am.movieid = m.movieid and a.actorid = am.actorid and m.movieid = :movieid")
            actors = db_conn.execute(query, movieid=id)
            save['actors'] = []
            for a in actors:
                save['actors'].append(a[0])
            # Find all the related movies (same genres)
            # Save the movie in the database
            dic.append(save)





        for e in dic:
            aux={}
            candidates = []
            amount = 0

            e["most_related_movies"] = []
            e["related_movies"] = []
            i = i + 1
            print("Movie " + str(i) + " of " + str(len(movies)))
            if e['genres']:
                for e2 in dic:
                    coincidence=0
                    if len(set(e['genres']) & set(e2['genres']))==len(e['genres']) and e is not e2:
                        e["most_related_movies"].append({'title':e2['title'], 'year':e2['year']})
                    elif len(set(e['genres']) & set(e2['genres']))>=float(float(len(e['genres']))/2) and e is not e2:
                        coincidence=float(len(set(e['genres']) & set(e2['genres'])))
                        #print(str(coincidence)+" / "+str(len(e['genres']))+" = "+str(int(coincidence*100/float(len(e['genres'])))))
                        #print(str(float(float(len(e['genres']))/2)))
                        e["related_movies"].append({'title':e2['title'], 'year':e2['year'], 'coincidence':int(coincidence*100/float(len(e['genres'])))})
                        
                e['related_movies'].sort(key=sorter)
                e['related_movies']=e['related_movies'][-10:]
                e['most_related_movies']=e['most_related_movies'][:10]
        try:
            client_movies.insert_many(dic)
        except:
            print("Error inserting the movie in the database")
            traceback.print_exc()
            pass
            
                

        
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if db_conn is not None:
            db_conn.close()

def sorter(e):
  return e['coincidence']

def main():
    # configurar el motor de sqlalchemy
    

    # check if si1 database exists in mongodb
    
    topUK()

__main__ = main()

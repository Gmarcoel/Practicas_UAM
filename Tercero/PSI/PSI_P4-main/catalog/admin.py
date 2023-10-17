from django.contrib import admin
from .models import Author, Book, Comment

admin.site.register(Book)
admin.site.register(Author)
admin.site.register(Comment)

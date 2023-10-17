
from django.urls import path
from . import views


urlpatterns = [
    path('', views.BookListView, name='books'),
    path('<slug>', views.BookDetailView, name='detail'),
    # path('<slug>', views.book_detail.as_view(), name='detail'),
    path('search/', views.SearchResultsView.as_view(), name='search'),
]

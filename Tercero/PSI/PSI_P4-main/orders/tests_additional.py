# created by R. Marabini
# Uncomment if you want to run tests in transaction mode with a final rollback
from django.test import TestCase
#uncomment this if you want to keep data after running tests
#from unittest import TestCase

from django.urls import reverse
from django.test import Client
from catalog.models import Book, User
from django.conf import settings
from .cart import Cart
from decimal import Decimal
from catalog.management.commands.populate import Command
from .forms import CartAddBookForm

from . import views

class AdditionalTestModels(TestCase):

    def test_cart_list_user_not_authenticated(self):
        """
        Test cart list with not authenticated user
        """
        # go to cart_list url
        url = reverse('cart_list')
        # create a client
        client = Client()
        # get the response
        response = client.get(url)
        # check the response status code is 302
        self.assertEqual(response.status_code, 302)
        # check the response url is login
        self.assertEqual(response.url, "/authentication/login/")
   

    def test_cart_add_with_not_authenticated_user(self):
        """
        Test cart add with not authenticated user
        """
        # go to cart_add url
        url = reverse('cart_add', kwargs={'slug': 'test-book'})
        # create a client
        client = Client()
        # get the response
        response = client.get(url)
        # check the response status code is 302
        self.assertEqual(response.status_code, 302)
        # check the response url is login
        self.assertEqual(response.url, "/authentication/login/")



    def test_cart_remove_with_not_authenticated_user(self):
        """
        Test cart remove with not authenticated user
        """
        # go to cart_list url
        url = reverse('cart_remove', kwargs={'slug': 'test-book'})
        # create a client
        client = Client()
        # get the response
        response = client.get(url)
        # check the response status code is 302
        self.assertEqual(response.status_code, 302)
        # check the response url is login
        self.assertEqual(response.url, "/authentication/login/")

    def test_order_create_with_not_authenticated_user(self):
        """
        Test order create with not authenticated user
        """
        # go to cart_list url
        url = reverse('order_create')
        # create a client
        client = Client()
        # get the response
        response = client.get(url)
        # check the response status code is 302
        self.assertEqual(response.status_code, 302)
        # check the response url is login
        self.assertEqual(response.url, "/authentication/login/")


    # tests that logs in a user and then calls order create without filling the form
    def test_order_create_with_authenticated_user_without_form(self):
        """
        Test order create with authenticated user without filling the form
        """
        user = {"username": "user_1",
                "password": "trampolin_1",
                "first_name": "name_1",
                "last_name": "last_1",
                "email": "email_1@gmail.com"}
        User.objects.create_user(**(user))
        
        # go to cart_list url
        url = reverse('order_create')
        # create a client
        client = Client()
        # log in the user
        response = client.post(reverse('login'),
                            {'username': user['username'],
                             'password': user['password']},
                            follow=True)
        self.assertTrue(response.context['user'].is_active)
        # get the response
        response = client.get(url)
        # check the response status code is 200
        self.assertEqual(response.status_code, 200)
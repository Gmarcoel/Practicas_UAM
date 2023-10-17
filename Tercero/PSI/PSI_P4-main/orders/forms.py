from django import forms
from .models import Order


class CartAddBookForm (forms.Form) :
    quantity = forms.IntegerField (min_value=1, max_value=100)


class OrderCreateForm (forms.Form) :
    first_name = forms.CharField (max_length=50)
    last_name = forms.CharField (max_length=50)
    email = forms.EmailField ()
    address = forms.CharField (max_length=100)
    postal_code = forms.CharField (max_length=20)
    city = forms.CharField (max_length=100)     
    
    def save(self, commit=True):
        if self.is_valid():
            data=self.cleaned_data
            order = Order()
            order.first_name = data['first_name']
            order.last_name = data['last_name']
            order.email = data['email']
            order.address = data['address']
            order.postal_code = data['postal_code']
            order.city = data['city']
            if commit:
                order.save()
            return order
    
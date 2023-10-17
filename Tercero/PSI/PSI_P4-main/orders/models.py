from django.db import models
from catalog.models import Book
from django.contrib.auth.models import User
from django.utils import timezone


# Create your models here.
#crear modelo order(order id, first name, last name, email, address, postal code, city, created, updated, paid)
class Order(models.Model):
    first_name = models.CharField(max_length=50, null=False)
    last_name = models.CharField(max_length=50, null=False)
    email = models.EmailField(max_length=100, null=False)
    address = models.CharField(max_length=100, null=False)
    postal_code = models.CharField(max_length=20, null=False)
    city = models.CharField(max_length=100, null=False)
    created = models.DateTimeField(default = timezone.now, null=False)
    updated = models.DateTimeField(default = timezone.now, null=False)
    paid = models.BooleanField(default=False, null=False)
    
    def __str__(self):
        return f'{self.id}'

    class Meta:
        db_table = 'orders'
    
    def get_total_cost(self):
        return sum(item.price * item.quantity for item in self.items.all())

        
class OrderItem(models.Model):
    order = models.ForeignKey(Order, on_delete=models.CASCADE, null=False, related_name='items')
    book = models.ForeignKey(Book, on_delete=models.CASCADE, null=False)
    price = models.DecimalField(max_digits=10, decimal_places=2, null=False)
    quantity = models.IntegerField(null=False)

    class Meta:
        db_table = 'order_items'
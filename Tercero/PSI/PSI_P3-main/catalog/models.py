from django.db import models
from django.template.defaultfilters import slugify
# Used to generate URLs by reversing the URL patterns
from django.urls import reverse
from django.contrib.auth.models import User
from datetime import date


# Model for the author
class Author(models.Model):
    """Model representing an author."""
    first_name = models.CharField(max_length=100)
    last_name = models.CharField(max_length=100)

    class Meta:
        ordering = ['last_name', 'first_name']

    def __str__(self):
        """String for representing the Model object."""
        return f'{self.last_name}, {self.first_name}'


# Books
class Book(models.Model):
    """Model representing a book (but not a specific copy of a book)."""
    isbn = models.CharField('ISBN', max_length=13, unique=True,
                            help_text='13 Character <a href="https:\
                            //www.isbn-international.org/content/what-isbn\
                            ">ISBN number</a>')

    title = models.CharField(max_length=200)

    price = models.DecimalField(decimal_places=2,
                                max_digits=1000)
    path_to_cover_image = models.CharField(max_length=200,
                                           null=True, blank=True,
                                           default="")
    number_copies_stock = models.IntegerField()
    date = models.DateField(default=date.today)
    score = models.PositiveIntegerField()
    slug = models.SlugField(max_length=200, null=True, blank=True)
    author = models.ManyToManyField(Author)

    def save(self, *args, **kwargs):
        """Override the save method to set the slug field."""
        self.slug = slugify(self.title)
        if self.path_to_cover_image == "":
            self.path_to_cover_image = "images/" + slugify(self.title) + ".jpg"

        super(Book, self).save(*args, **kwargs)

    def __str__(self):
        """String for representing the Model object."""
        return self.title

    def get_absolute_url(self):
        """Returns the url to access a detail record for this book."""
        return reverse('detail', args=[str(self.slug)])


# Model for the comments
class Comment(models.Model):
    date = models.DateField(default=date.today)
    msg = models.TextField()
    book = models.ForeignKey(Book, on_delete=models.RESTRICT, null=True)
    user = models.ForeignKey(User, on_delete=models.RESTRICT, null=True)

    def __str__(self):
        """String for representing the Model object."""
        return self.msg

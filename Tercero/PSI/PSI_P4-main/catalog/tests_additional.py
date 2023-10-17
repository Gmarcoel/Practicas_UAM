from .views import SearchResultsView, BookDetailView, BookListView
from django.test import RequestFactory
from django.test import TestCase
from django.urls import reverse

from bookshop.settings import BASE_DIR
from decimal import Decimal

pathToProject = BASE_DIR
from .models import Author as Author
from .models import Book as Book
from .models import User as User
from .models import Comment as Comment
from django.test import Client, TestCase
from .management.commands.populate import Command

DETAIL_SERVICE = "detail"
SEARCH_SERVICE = "search"
SEARCH_TITLE = "Search"

SERVICE_DEF = {DETAIL_SERVICE: {
        "title": "",
    },
    SEARCH_SERVICE: {
        "title": SEARCH_TITLE,
    },
}


# Nuevos tests
class AditionalTestsModels(TestCase):
    
    def setUp(self):
        self.authorDict = {
            "first_name": 'Pedro',
            "last_name": 'Picapiedra',
        }
        self.bookDict = {
            "isbn": '1234567890123',
            "title": 'title_1',
            "price": Decimal(23.32),
            "path_to_cover_image": 'kk.jpg',
            "number_copies_stock": 23,
            "score": 9,
        }
        self.userDict = {
            "username": 'pmarmol',
            "password": 'troncomovil',
            "first_name": 'Pablo',
            "last_name": 'Marmol',
            "email": 'p.marmol@cantera.com',
        }

    def create_check(self, dictionary, ObjectClass):
        """ create an object of the class 'ObjectClass'
        using the dictionary. Then,
        check that all key-values in the
        dictionary are attributes in the object.
        return created object of class Object
        """
        # check that str function exists
        self.assertTrue(ObjectClass.__str__ is not object.__str__)
        # create object
        item = ObjectClass.objects.create(**dictionary)
        for key, value in dictionary.items():
            self.assertEqual(getattr(item, key), value)
        # execute __str__() so all the code in models.py is checked
        item.__str__()
        return item

    # Nuevos tests
    def test05_book_with_authors(self):
        "Test book model with authors"
        book = self.create_check(self.bookDict, Book)
        a1 = self.create_check(self.authorDict, Author)
        a2 = self.create_check(self.authorDict, Author)
        book.author.add(a1)
        book.author.add(a2)
        book.save()
        self.assertEqual(len(book.author.all()), 2)
        for author in book.author.all():
            self.assertEqual(self.authorDict['first_name'], author.first_name)
            self.assertEqual(self.authorDict['last_name'], author.last_name)
        # It should be possible to recover the books from Author objects
        bookA1 = a1.book_set.all()[0]
        self.assertEqual(bookA1.pk, book.pk)
    
    def test06_book_with_authors_and_comments(self):
        "Test book model with authors and comments"
        book = self.create_check(self.bookDict, Book)
        a1 = self.create_check(self.authorDict, Author)
        a2 = self.create_check(self.authorDict, Author)
        book.author.add(a1)
        book.author.add(a2)
        book.save()
        self.assertEqual(len(book.author.all()), 2)
        for author in book.author.all():
            self.assertEqual(self.authorDict['first_name'], author.first_name)
            self.assertEqual(self.authorDict['last_name'], author.last_name)
        # It should be possible to recover the books from Author objects
        bookA1 = a1.book_set.all()[0]
        self.assertEqual(bookA1.pk, book.pk)
        commentDict = {"book": book,
                       "user": self.create_check(self.userDict, User),
                       "msg": "this is a comment"}
        c1 = self.create_check(commentDict, Comment)
        self.assertEqual(c1.user.pk, commentDict['user'].pk)
        self.assertEqual(c1.book.pk, commentDict['book'].pk)
        self.assertEqual(c1.msg, commentDict['msg'])

    # Test to check the get_absolute_url() method in Book
    def test07_book_get_absolute_url(self):
        "Test get_absolute_url() method in Book"
        book = self.create_check(self.bookDict, Book)
        self.assertEqual(book.get_absolute_url(), '/catalog/' + str(book.slug))
    
    
    # Test to check the save method in Book
    def test08_book_save(self):
        "Test save method in Book"
        book = self.create_check(self.bookDict, Book)
        book.path_to_cover_image = ""
        book.save()
        self.assertEqual(book.path_to_cover_image, 'images/' + str(book.slug) + '.jpg')

    # Test to check get_queryset in SearchResultsView class
    def test09_search_results_view_get_queryset(self):
        "Test get_queryset in SearchResultsView"
        book = self.create_check(self.bookDict, Book)
        book.save()
        request = RequestFactory().get('/catalog/search/?q=' + str(book.title))
        response = SearchResultsView.as_view()(request)
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.context_data['object_list'][0].pk, book.pk)
        
    # Test to check bookDetailView function
    # def test10_book_detail_view(self):
        


    """
    # Test to check bookDetailView class
    def test10_book_detail_view(self):
        "Test bookDetailView"
        book = self.create_check(self.bookDict, Book)
        book.save()
        request = RequestFactory().get('/catalog/')
        response = BookDetailView(request, book.slug)
        self.assertEqual(response.status_code, 200)
        
        

    
    # Test to check BookListView class
    def test11_book_list_view(self):
        "Test BookListView"
        book = self.create_check(self.bookDict, Book)
        book.save()
        request = RequestFactory().get('/catalog/')
        response = BookListView(request)
        self.assertEqual(response.status_code, 200)
    """



class ServiceBaseTest(TestCase):
    def setUp(self):
        self.client1 = self.client
        self.client2 = Client()
        self.client3 = Client()
        self.populate = Command()
        self.populate.handle()

    def tearDown(self):
        self.populate.cleanDataBase()

    @classmethod
    def decode(cls, txt):
        return txt.decode("utf-8")


# Nuevos tests
class AditionalTestsServices(ServiceBaseTest):
        
    # Test to check __str__ in book model
    def test01_book_str(self):
        books = Book.objects.all()
        book = books[0]
        self.assertEqual(book.__str__(), book.title)
    
    # Test to check __str__ in author model
    def test02_author_str(self):
        authors = Author.objects.all()
        author = authors[0]
        self.assertEqual(author.__str__(), author.last_name+', '+author.first_name)
    
    # Test to check __str__ in comment model
    def test03_comment_str(self):
        comments = Comment.objects.all()
        comment = comments[0]
        self.assertEqual(comment.__str__(), comment.msg)
    
    # Test to check BookListView
    def test04_book_list_view(self):
        response = self.client1.get(reverse(BookListView))
        self.assertEqual(response.status_code, 200)
        self.assertTemplateUsed(response, 'home.html')

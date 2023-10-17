# Populate database
# This file has to be placed within the
# catalog/management/commands directory in your project.
# If that directory doesn't exist, create it.
# The name of the script is the name of the custom command,
# that is, populate.py.
#
# execute python manage.py  populate
#
import os
from django.core.management.base import BaseCommand
from catalog.models import (Author, Book, Comment)
from django.contrib.auth.models import User
from faker import Faker
# define STATIC_PATH in settings.py
from bookshop.settings import STATIC_PATH
from PIL import Image, ImageDraw, ImageFont


FONTDIR = "/usr/share/fonts/truetype/freefont/FreeMono.ttf"

# The name of this class is not optional must be Command
# otherwise manage.py will not process it properly
#


class Command(BaseCommand):
    # helps and arguments shown when command python manage.py help populate
    # is executed.
    help = """populate database
           """

    # def add_arguments(self, parser):

    # handle is another compulsory name, do not change it"
    # handle function will be executed by 'manage populate'
    def handle(self, *args, **kwargs):
        # check a variable that is unlikely been set out of heroku
        # as DYNO to decide which font directory should be used.
        # Be aware that your available fonts may be different
        # from the ones defined here
        if 'DYNO' in os.environ:
            self.font = \
                "/usr/share/fonts/truetype/dejavu/DejaVuSansMono-Bold.ttf"
        else:
            """
            self.font = \
                "/usr/share/fonts/truetype/freefont/FreeMono.ttf"
            """
            # Custom font
            self.font = os.path.join(STATIC_PATH,
                                     "fonts/OperatorMono-Medium.ttf")
        # self.font = ImageFont.load_default()

        self.NUMBERUSERS = 20
        self.NUMBERBOOKS = 30
        self.NUMBERAUTHORS = 10
        self.MAXAUTHORSPERBOOK = 3
        self.NUMBERCOMMENTS = self.NUMBERBOOKS * 5
        self.MAXCOPIESSTOCK = 30
        self.cleanDataBase()   # clean database
        # The faker.Faker() creates and initializes a faker generator,
        self.faker = Faker()
        self.stdout.write("Creating users...")
        self.user()
        self.stdout.write("Creating authors...")
        self.author()
        self.stdout.write("Creating books...")
        self.book()
        self.stdout.write("Creating comments...")
        self.comment()
        # check a variable that is unlikely been set out of heroku
        # as DYNO to decide which font directory should be used.
        # Be aware that your available fonts may be different
        # from the ones defined here

    def cleanDataBase(self):
        self.stdout.write("Deleting old data...")
        models = [Comment, Book, User, Author]
        for m in models:
            m.objects.all().delete()
        path = os.path.join(STATIC_PATH, "images/")
        for root, dirs, files in os.walk(path):
            for file in files:
                os.remove(os.path.join(root, file))

    def user(self):
        User.objects.create_superuser(
            username='alumnodb',
            email='',
            password='alumnodb')

        for i in range(self.NUMBERUSERS):
            user = User.objects.create_user(
                username=self.faker.user_name(),
                first_name=self.faker.user_name(),
                last_name=self.faker.user_name(),
                email=self.faker.email(),
                password=self.faker.password())
            user.save()
            # self.stdout.write("User %s created" % user.username)

    def author(self):
        for i in range(self.NUMBERAUTHORS):
            author = Author.objects.create(
                first_name=self.faker.first_name(),
                last_name=self.faker.last_name())
            author.save()
            # self.stdout.write("Author %s created" % author.first_name)

    def cover(self, book):
        """create fake cover image.
           This function creates a very basic cover
           that show (partially),
           the primary key, title and author name"""

        img = Image.new('RGB', (200, 300), color=(8, 92, 15))
        # your font directory may be different

        fnt = ImageFont.truetype(
            str(self.font),
            16, encoding="unic")
        d = ImageDraw.Draw(img)
        d.text((10, 50), "PK %05d" % book.id, font=fnt, fill=(255, 255, 255))
        d.text((20, 150), book.title[:15], font=fnt, fill=(255, 255, 255))
        d.text((20, 200), "By %s" % str(
            book.author.all()[0])[:15], font=fnt, fill=(255, 255, 255))
        img.save(os.path.join(STATIC_PATH, book.path_to_cover_image))

    def book(self):
        for i in range(self.NUMBERBOOKS):
            book = Book.objects.create(
                isbn=self.faker.isbn13(separator=""),
                title=self.faker.sentence(nb_words=4, variable_nb_words=True),
                number_copies_stock=self.faker.random_int(
                                            min=1, max=self.MAXCOPIESSTOCK),
                date=self.faker.date_time_between(
                    start_date="-30y", end_date="now", tzinfo=None),
                price=self.faker.pydecimal(left_digits=None, right_digits=2,
                                           positive=True, min_value=None,
                                           max_value=100),
                score=self.faker.random_int(min=0, max=10),
                )
            # path_to_cover_image = "images/"+ str(book.isbn)+".jpg"
            i = self.faker.random_int(min=0, max=2)
            while i < 3:
                auth = self.faker.random_element(elements=list(
                                                 Author.objects.all()))
                book.author.add(auth)
                i += 1
            book.save()
            self.cover(book)

    def comment(self):
        for i in range(self.NUMBERCOMMENTS):
            comment = Comment.objects.create(
                date=self.faker.date_time_between(
                    start_date="-30d", end_date="now"),
                msg=self.faker.text(max_nb_chars=200),
                book=self.faker.random_element(elements=list(
                                               Book.objects.all())),
                user=self.faker.random_element(elements=list(
                                               User.objects.all()))
                )
            comment.save()
            # self.stdout.write("Comment %s created" % comment.msg)
        pass

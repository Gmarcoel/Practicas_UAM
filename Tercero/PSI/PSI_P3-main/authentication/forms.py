from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User


# Inheritance of UserCreationForm
# with the new arguments needed for
# the user registration
class SignUpForm(UserCreationForm):

    class Meta:

        model = User
        fields = ("username",
                  "first_name", "last_name",
                  "email", )

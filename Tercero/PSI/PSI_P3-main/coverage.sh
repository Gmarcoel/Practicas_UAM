coverage erase
coverage run --omit="*/test*" --source=catalog ./manage.py test catalog
coverage report -m -i > coverage.txt
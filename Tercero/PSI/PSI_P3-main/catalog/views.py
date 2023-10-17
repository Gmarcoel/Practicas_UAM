from django.shortcuts import render
from django.views import generic
from .models import Book, Comment
from django.db.models import Q


# class for search result view
class SearchResultsView(generic.ListView):
    model = Book
    paginate_by = 5
    template_name = 'catalog/search_results.html'

    def get_queryset(self):
        query = self.request.GET.get('q')
        object_list = Book.objects.filter(
            Q(title__icontains=query) |
            Q(author__first_name__icontains=query) |
            Q(author__last_name__icontains=query)
        ).distinct().order_by('-date')
        return object_list


# class that shows the book details and comments
class book_detail(generic.DetailView):
    model = Book
    # Show comments for a book

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['comments'] = Comment.objects.filter(book__id=self.object.id)
        return context


# Book list view
def BookListView(request):
    popularBooks = Book.objects.order_by('-score')[:5]
    recentBooks = Book.objects.order_by('-date')[:5]
    return render(request, 'home.html', context={
                  'popularBooks': popularBooks, 'recentBooks': recentBooks})

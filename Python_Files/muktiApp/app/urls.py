from django.conf.urls import url, include

from . import views

urlpatterns = [
        url(r'^notif/$', views.getNotif, name='getNotif'),
        ]
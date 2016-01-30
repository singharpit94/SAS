from django.http import HttpResponse
from django.shortcuts import render, redirect, render_to_response
from django.core import serializers
from .models import Notif


def getNotif(request):
    newNotif = Notif.objects.all().order_by('-date')[:10]
    data = serializers.serialize('json',newNotif)
    return HttpResponse(data, content_type='application/json')

from django.db import models
from datetime import datetime
from django.contrib import admin
# Create your models here.

class Notif(models.Model):
    text = models.CharField(max_length=200)
    date = models.DateTimeField(datetime.now)

    def __unicode__(self): return self.text

admin.site.register(Notif)
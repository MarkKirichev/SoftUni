# Generated by Django 3.1.4 on 2020-12-10 16:44

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('blogs', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='blog',
            name='slug',
            field=models.SlugField(default=''),
            preserve_default=False,
        ),
    ]

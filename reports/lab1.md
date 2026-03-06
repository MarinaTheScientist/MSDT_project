# Лабораторная работа №1. Базовая работа с git
**Студент:** Мельник Егор\
**Группа:** 5130201/50001\
**Цель работы:** Познакомиться с базовыми операциями Git.

## Содержание
1. Установка и настройка
2. Начало работы с новым проектом
3. Отслеживание состояния кода
4. Откат изменений
5. Ветвление и слияние
6. Работа с удалённым репозиторием
7. История изменений
8. Выводы
9. Источники

## Установка и настройка
**Цель:** Установить и настрить git\
**Команды:**
```bash
git --version
git config --global user.name "melnik_egor"
git config --global user.email "loldota2pubg@gmail.com"
git --help
```
**Вывод Команд:**

`git --version` -> 
 `git version 2.53.0.windows.1`\
 Команда выводит установленную версию git.
***
Команды `git config --global user.name "melnik_egor"` и 
`git config --global user.email "loldota2pubg@gmail.com"` используются для настройки подписи автора коммитов. 
***
Команда `git --help` выводит список самых популярных команд:

![Screenshot_478.png](imgs\Screenshot_478.png)

## Начало работы с новым проектом
Я создал файл `my_projects` и там же новый репозиторий. Затем в этом репозитории файл `README.md`, дерикторию `reports` и файл `reports/lab1.md`.

Основные синтаксические элементы языка Markdown, который используется для содержимого файлов `.md` [(Источник)](https://skillbox.ru/media/code/yazyk-razmetki-markdown-shpargalka-po-sintaksisu-s-primerami/#:~:text=*%20%D0%9D%D1%83%D0%BC%D0%B5%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%BD%D1%8B%D0%B5%20(ordered)%20*%20%D0%9D%D0%B5%D0%BD%D1%83%D0%BC%D0%B5%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%BD%D1%8B%D0%B5%20(unordered)%20*,%D0%92%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%BD%D1%8B%D0%B5%20(nested)%20*%20%D0%94%D1%80%D1%83%D0%B3%D0%B8%D0%B5%20%D1%8D%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82%D1%8B%20%D0%B2%D0%BD%D1%83%D1%82%D1%80%D0%B8%20%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%BE%D0%B2):
### Загловки
![Screenshot_480.png](imgs\Screenshot_480.png)
### Выделение текста
#### Курсив (italic)
![Screenshot_481.png](imgs\Screenshot_481.png)
#### Жирный (bold)
![Screenshot_482.png](imgs\Screenshot_482.png)
#### Жирный курсив (bold and italic)
![Screenshot_483.png](imgs\Screenshot_483.png)
### Зачёркнутый
![Screenshot_485.png](imgs\Screenshot_485.png)
### Подчёркнутый
![Screenshot_486.png](imgs\Screenshot_486.png)
### Разделители 
![Screenshot_487.png](imgs\Screenshot_487.png)
### Цитаты
![Screenshot_488.png](imgs\Screenshot_488.png)
### Списки
![Screenshot_489.png](imgs\Screenshot_489.png)
### Ссылки
![Screenshot_492.png](imgs\Screenshot_492.png)
![Screenshot_493.png](imgs\Screenshot_493.png)
### Картинки
Изображения в Markdown оформляются по принципу, схожему с принципом оформления ссылкок, только перед квадратными скобками нужно поставить восклицательный знак.

Можно указать либо ссылку на изображение:  
\![Изображение]\(https://upload.wikimedia.org/wikipedia/commons/thumb/4/48/Markdown-mark.svg/1920px-Markdown-mark.svg.png "Логотип Markdown")

Либо путь к изображению:   
\![Screenshot_493.png]\(imgs\Screenshot_493.png)
### Вставка кода
![Screenshot_494.png](imgs\Screenshot_494.png)
### Таблицы
![Screenshot_495.png](imgs\Screenshot_495.png)

Написал в файле README.md заголовок, информацию о дисциплине и о себе. Создал коммит с файлами `README.md` и `reports/lab1.md`.

## Отслеживание состояния кода
**Команды:**
```bash
git status
git diff
```
**Вывод Команд:**
![Screenshot_496.png](imgs\Screenshot_496.png)
*Эта команда показывает текущее состояние рабочей директории и индекса. В данном случае нет изменений.*

![Screenshot_497.png](imgs\Screenshot_497.png)
*Эта команда построчно сравнивает содержимое файлов. По умолчанию она показывает разницу между рабочей директорией и индексом. В данном случае нет изменений.*
***
Я внес заметки по предыдущим этапам в файл `reports/lab1.md`. При повторном использовании команды выводят:

![Screenshot_497.png](imgs\Screenshot_498.png)
*Файл `lab1.md` изменен, но не добавлен в индекс.*

![Screenshot_497.png](imgs\Screenshot_499.png)
*Измениния в файле `lab1.md`*
***
C помощью команды `git add .` я добавил изменения в индекс. Теперь команда `git status` показывает:

 ![Screenshot_500.png](imgs\Screenshot_500.png)
*Измениния находяться в индексе и их можно коммитить.*
***
Я внес изменения в файле `README.md` и команда `git diff README.md` показывает изменения сделанные только в этом файле: 

 ![Screenshot_501.png](imgs\Screenshot_501.png)

## Откат изменений

Я использовал команду `git restore` и измениня файла `README.md` пропали.

Я удалил файл `lab1.md` и ввел команду `git status`:

![Screenshot_502.png](imgs\Screenshot_502.png)
*Команда показывает то, что изменения произошли, а именно то, что файл был удален.*

Я его восстановил с помощью команды `git restore`.

## Ветвление версий

Я вывел имя текущей ветки с помощью команды `git branch` -> `main` и создал новую ветку `lab1-1` с помощью команды `git checkout`. 
Дополнил отчет и закоммитил измения. 
Я переключился на изначальную ветку и измения остались в ветке `lab1-1`. Далее я внес измения в файл `README.md` и попробовал переключится на другую ветку. Программа вывела:

![Screenshot_503.png](imgs\Screenshot_503.png)
*Буква "M" (___Modified___) сообщает, что файл `README.md` был изменён в рабочей директории, но эти изменения не были закоммичены на предыдущей ветке.*

## Слияние веток, конфликты

Я откатил изменения в файле `README.md` с помощью команды `git restore`. 

лабуба
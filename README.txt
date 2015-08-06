GestNotes - Version 1.0 - Version Qt 5.4.1 / Apache 2.4.9 - 04/13/2015

GENERAL USAGE NOTES
--------------------

- This program do not support Linux and Mac OS, and could not support Windows OS older than Seven.

- The application need to import a MySql database in an existing database. The file to import the database can be found under the /database folder.

- If you have never used a MySql database follow these steps :
	1 - Download Wamp (Windows OS) or Lamp (Linux OS)
	2 - In a web browser, enter 127.0.0.1 in the address bar
	3 - Click on "phpmyadmin" under the tab "Tools"
	4 - Once connected to phpMyAdmin click the "Databases" tab
	5 - Create a new database under the "Create database" tab and click on it (name it "gestnotes" for instance)
	6 - Click on the "Import" tab and select the file under the /database folder
	7 - Click on "Go"
	8 - You can now connect to your local MySql database
	9 - Host : 127.0.0.1 - User : root - Password : Any (by default) - DataBase : gestnotes (example)

- There are 2 administrators on the database : 20120000 and 20120001.

FEATURES
--------------------

- The interface of this application depends on who is connected to it.

- Administrator :
	- Display all users / administrato / professors / students
	- Display modules and specialities
	- Add / update / remove users
	- Update the module that a professor is in charge
	- Update the student that a professor is tutoring
	- Admit a student in the upper class

- Professor :
	- Change grade for his modules
	- Display tutored students

- Student :
	- Display grade for his modules
	- Update his speciality




	
# Dog-Shelter

A software application developed with C++ and Qt6 framework for managing dogs from shelters, having two main modes (admin mode and user mode).

## Admin mode features
- A table with all the dogs from the shelter and their photos
- Add a new dog
- Remove an existing dog
- Update the information of an existing dog

## User mode features
- A table showing all the adopted dogs
- A window showing the dogs one by one allowing the user to either adopt or skip the current dog. A filter option (by age and breed) is provided
- Statistics option having a pie chart and a bar chart for displaying the distribution of dog breeds in the shelter 
- Externally view of the adoption list as HTML or CSV table
  
## Used Concepts and Several Aplication Features
- Layered Architecture: ```presentation layer``` (application UI), ```business layer``` (aplication service), ```persistance layer``` (aplication repositories)
- Usage of important Object Oriented Programming concepts, such as: ```abstraction```, ```encapsulation```, ```inheritance``` and ```polymorphism```. Example of ```inheritance``` usage: in the persistance layer, abstract templated class *Repository* is inherited by the derived classes *FileRepository*, *HTMLRepository* and *CSVRepository*. The aplication's service maintains a pointer to the user's repository which can have the type *HTMLRepository* or *CSVRepository* depending on the user's choice - ```polymorphism```
- Usage of Qt ```signals``` and ```slots```
- Exceptions handling
- Unit testing
- Unlimited ```undo/redo``` operations for adding, removing and updating in the admin's database and adoption list

## Design Patterns that were used
- ```Model-View-Controller``` design pattern for showing the database in the table, together with custom Qt delegates for showing the dog's photos
- ```Command``` design pattern for the undo/redo operations, a list of operations is maintained (for each function and its arguments)
  
## Screenshots

### Choose aplication mode
<p align="center">
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/choose_mode.png" height ="400" width="450"><img/>
</p>

### Admin mode
<p align="center">
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/admin_menu.png" height="400"><img/>
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/add_dog.png" height="300"><img/>
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/update_dog_info.png" height="300"><img/>
</p>

### User mode
<p align="center">
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/user_menu.png" width="400"></img>
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/filter.png" width="250"></img>
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/pie_chart.png" width="400"></img>
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/bar_chart.png" width="400"></img>
</p>
<p align="center">
<img src="https://github.com/vladutpasare12/Dog-Shelter/blob/main/screenshots/html_table.png" height="200"></img>
</p>

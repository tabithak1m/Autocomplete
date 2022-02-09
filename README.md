# Autocomplete

### ESC190 Project

This project is an implementation of the autocomplete function. Each time a letter is typed, there will be suggested terms for autocomplete. The terms will be read in from any file containing a large number of terms with their own importance weight next to them formatted like the provided cities.txt file. These terms will be sorted using lexiographical ordering, finding the highest match for the autocomplete suggestion. Here, the function finding this will be done ran in O(log(n terms)) as a greater complexity will significantly slow down the program due to the large amount of terms. 

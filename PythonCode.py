'''
   Jen Nadeau
   CS 210 
   Project 3: Corner Grocer
   PythonCode.py
'''

import re
import string

# Python function to read and display list of items and quantity of each purchased
def read_file():
    # Reads file and sorts items
    contents = open('CS210_Project_Three_Input_File.txt')
    product_list = contents.read().split()
    products = sorted(set(product_list))

    # Displays item and number of times item appears
    for word in products:
        print(word + ":" , product_list.count(word))
        print()

    # Closes file
    contents.close()

# Python function to return number of times a specific item was purchased
def specific_item_quantity(v):
    # Reads file and sorts items into list 
    contents = open('CS210_Project_Three_Input_File.txt' , 'r')
    product_list = contents.read().split()
    products = sorted(set(product_list))

    quantity = 0
    num_items_total = 0
    num_items = 0

    # Obtains total number of items in list
    for word in products:
        num_items_total += 1

    # Obtains number of times item was purchased, if at all
    for word in products:
        temp_word = word
        num_items += 1

        if (temp_word == v.capitalize()):
            quantity = product_list.count(word)
            num_items -= 1
        if (temp_word != v and num_items == num_items_total):
            return -1

    return quantity

# Python function to read input file and create a new one  
def read_and_create_file():
    # Reads file and sorts items into list 
    contents = open('CS210_Project_Three_Input_File.txt' , 'r')
    product_list = contents.read().split()
    products = sorted(set(product_list))

    # Opens empty file to write to
    new_file = open('frequency.dat' , 'w')

    # Writes data to new file as product and number purchased
    for word in products:
        new_file.write(word)
        new_file.write(" ")
        new_file.write(str(product_list.count(word)))
        new_file.write("\n")

    # Close files
    contents.close()
    new_file.close()

    return new_file
    
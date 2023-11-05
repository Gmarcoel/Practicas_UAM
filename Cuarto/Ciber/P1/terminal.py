#!/usr/bin/env python
# encoding: utf-8
import npyscreen
import time
import curses
import threading

class DroneApp(npyscreen.NPSApp):
    command = ""
    def main(self):
        # These lines create the form and populate it with widgets.
        # A fairly complex screen in only 8 or so lines of code - a line for each control.
        self.F  = npyscreen.FormBaseNew(name = "Drone Control Center",)
        y, x = self.F.useable_space()
        
        self.status_widget = self.F.add(StatusWidget, name="Status", editable=False, max_height = 5)
        self.info_widget = self.F.add(InfoWidget, name="Info", editable=False, max_height = 13)
        self.input_box = self.F.add(InputBox, name="Terminal", max_height = 5)
        self.input_box.change(self.funcion_x)
        # output_widget = F.add(StatusWidget, editable=False)
        # This lets the user interact with the Form.
        self.F.edit()
        
        
    def updateInfo(self, msg):
        self.info_widget.update_output(msg)
        self.F.display()
        # self.F.display()

    def updateStatus(self, msg):
        pass
        self.status_widget.update_output(msg)
        self.F.display()
        # self.F.display()

    def die(self):
        self.F.editing = False
        self.F.erase()

    def update_name(self, name):
        self.F.name = "Drone " + name + " Control Center"
        self.F.display()

    def funcion_x(self):
        #print(self.input_box.value)
        if '\n' in self.input_box.value:
            self.command = self.input_box.value[:-1]
            # self.command[0] = self.command[0].lower()
            self.input_box.value = ''


class EtApp(npyscreen.NPSApp):
    loading=True
    command = ""
    drone_status = {}
    def main(self):
        self.F  = npyscreen.FormBaseNew(name = "ET Control Center",)

        self.status_widget = self.F.add(MultipleStatusWidget, name="Status", editable=False, max_height = 10)
        self.info_widget = self.F.add(InfoWidget, name="Info", editable=False, max_height = 8)
        self.input_box = self.F.add(InputBox, name="Terminal", max_height = 1)
        self.input_box.change(self.funcion_x)
        self.loading=False
        self.F.edit()

    def updateInfo(self, msg):
        self.info_widget.update_output(msg)
        self.F.display()

    def getStatus(self):
        return self.drone_status

    def removeDroneStatus(self, id):
        del self.drone_status[id]
        self.status_widget.update_output(list(self.drone_status.values()))
        self.F.display()

    def updateStatus(self, id, msg):
        self.drone_status[id] = msg
        self.status_widget.update_output(list(self.drone_status.values()))
        self.F.display()

    def die(self):
        self.F.editing = False
        self.F.erase()

    def update_name(self, name):
        self.F.name = "ET " + name + " Control Center"
        self.F.display()
        
    def funcion_x(self):
        if '\n' in self.input_box.value:
            self.command = self.input_box.value[:-1]
            # self.command[0] = self.command[0].lower()
            self.input_box.value = ''

class BoApp(npyscreen.NPSApp):
    command = ""
    full_status = {}
    def main(self):
        self.F  = npyscreen.FormBaseNew(name = "BO Control Center",)
        self.status_widget = self.F.add(MultipleStatusWidget, name="Status", editable=False, max_height = 10)
        self.info_widget = self.F.add(InfoWidget, name="Info", editable=False, max_height = 8)
        self.input_box = self.F.add(InputBox, name="Terminal", max_height = 1)
        self.input_box.change(self.funcion_x)
        
        self.F.edit()


    def updateInfo(self, msg):
        self.info_widget.update_output(msg)
        self.F.display()

    def updateStatus(self, msg):
        # self.status_widget.update_outputs(id, msg)
        # self.info_widget.update_output(msg)
        self.status_widget.update_output(msg)
        self.F.display()
        

    def funcion_x(self):
        if '\n' in self.input_box.value:
            self.command = self.input_box.value[:-1]
            # self.command[0] = self.command[0].lower()
            self.input_box.value = ''

    def die(self):
        self.F.editing = False
        self.F.erase()

class InputBox(npyscreen.BoxTitle):
    _contained_widget = npyscreen.MultiLineEdit 
    _contained_widget.value = ""
    def change(self, funcion_x):
        self._contained_widget.when_value_edited = funcion_x
        # self.F.display()
       

class MultipleStatusWidget(npyscreen.BoxTitle):
    status = []
    _contained_widget = npyscreen.Pager
    # _contained_widget.name = " "
    def update_output(self, output):
        self.values = output
        self.update()



class StatusWidget(npyscreen.BoxTitle):
    _contained_widget = npyscreen.FixedText
    def update_output(self, output):
        self.value = output
        self.update()
        # self.display()

class InfoWidget(npyscreen.BoxTitle):
    info = []
    _contained_widget = npyscreen.Pager
    # _contained_widget.name = " "
    def update_output(self, output):
        if len(self.info)>5:
            self.info.pop(0)
        self.info.append(output)
        self.values = self.info
        self.update()





    

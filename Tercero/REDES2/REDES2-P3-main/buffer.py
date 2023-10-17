import time

class BufferCircular:

    size = 0
    buffer = []


    def __init__(self, fps):
        self.size = fps*2
        self.buffer = []
    
    def insertar(self, dato):
        for i in range(len(self.buffer)):
            if self.buffer[i]['ord'] > dato['ord']:
                self.buffer.insert(i, dato)
                return True
        if len(self.buffer) < self.size:
            self.buffer.append(dato)
        return False if self.lleno() else True
    
    def extraer(self):
        return self.buffer.pop()
    
    def vacio(self):
        if len(self.buffer) == 0:
            return True
        else:
            return False

    def lleno(self):
        if len(self.buffer) == self.size:
            return True
        else:
            return False

    def getTime(self):
        return self.buffer[0]['time']
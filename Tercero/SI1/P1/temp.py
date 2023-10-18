import pickle  # .dat

class User:
   def __init__(self,id,username,password, email, creditcard):
      self.id = id
      self.password = password
      self.username = username
      self.email = email
      self.creditcard = creditcard
    


def main():
    print("jeje")
    data = User(17,"user", "email", "key", "creditcard")
    # Save in .dat
    #stuff = data.get(1.0, END)
    filename = "datos.dat"  # Create file
    output = open(filename, 'wb')
    pickle.dump(data, output)
    output.close()



    # Open .dat
    filename = os.getcwd() + "/usuarios/" + nombre_us +  "/datos.dat"
    input = open(filename, 'rb')
    
    stuff = pickle.load(input)
    input.close()
    
    print(stuff.username)

if __name__=="__main__":
    main()


import os

def must_open(dirpath, filename):
    """change this function to select if a file must be opened or not"""
    return True

def opened_files(*args):
    """generate a sequence of pairs (path to file, opened file)
    in a given directory. Same arguments as os.walk."""
    for dirpath, dirnames, filenames in os.walk(*args):
        for filename in filenames:
            if must_open(dirpath, filename):
                filepath = os.path.join(dirpath, filename)
                yield (filepath, open(filepath, "rU"))

# main loop:
mydir = "/home/user/path/to/my/dir"
for filepath, file in opened_files(mydir):
    # do something
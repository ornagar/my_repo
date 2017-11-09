import urllib2
import webbrowser, os
import requests

def search_wiki():
	request = raw_input("enter keyword to search wiki: ")
	url = "http://en.wikipedia.org/wiki"
	full_url = url + "/" + request
	data = urllib2.urlopen(full_url)
	with open("result.html", "w") as txt:
		txt.write(data.read())
		
	webbrowser.open('file://' + '/home/xyz/svn/Proj/src/python/' + 'result.html')
	webbrowser.exit()

#TODO: work on it
def copy_dictionary(path="dictionary.txt"):
    my_dictionary = {}
    new_str = ""
    with open(path, "r") as f:
        for line in f.readlines():
            if len(line.strip()) > 0:
                new_str = line.split(':')
                my_dictionary[new_str[0]] = new_str[1].strip()
    return my_dictionary



def my_post(dictionary):
    url = "http://posttestserver.com/post.php"
    r = requests.post(url, data=dictionary)
    print(r.status_code, r.reason)


class A:
	def __init__(self):
		self.x = 4
		


if __name__ == "__main__":
	#search_wiki()
	my_dict = {'number': 100, 'type': 'test', 'action': 'show'}
	#my_post(my_dict)
	#print copy_dictionary()
	a = A()
	print a.x
	a.y = 14
	print a.y
	a.__dict__
	

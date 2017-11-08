import urllib2

response = urllib2.urlopen('http://python.org/')
html = response.read()

import abc


class IParser(object):
	__metaclass__ = abc.ABCMeta
	
	@abc.abstractmethod
	def parse(self, data, t):
		pass
		
	@abc.abstractproperty
	def info(self):
		pass
		
class CParser(IParser):
	def parse(self, data):
		pass
	
	@property
	def info(self):
		return None

parser = CParser()
parser.parse()

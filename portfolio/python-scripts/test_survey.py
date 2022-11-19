import unittest
from survey import AnonimousSurvey

class TestAnonimousSurvey(unittest.TestCase):
	"""Test for the class AnonimousSurvey"""
	def setUp(self):
		"""create a survey and a set of responses for all tests"""
		question="what languages you speak"
		self.my_survey=AnonimousSurvey(question)
		self.responses=['english','spanish','portuguese']

	def test_store_single_response(self):
		"""test a single response is stored correctly"""

		self.my_survey.store_response(self.responses[0])
		self.assertIn(self.responses[0],self.my_survey.responses)

	def test_store_three_responses(self):
		"""try to store three responses"""
		
		for response in self.responses:
			self.my_survey.store_response(response)

		for response in self.responses:
			self.assertIn(response,self.my_survey.responses)

if __name__ == '__main__':
	unittest.main()
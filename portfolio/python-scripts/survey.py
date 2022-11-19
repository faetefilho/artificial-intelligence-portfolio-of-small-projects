class AnonimousSurvey:
	"""collect anonimous answers to survey questions"""

	def __init__(self, question):
		"""store a question and prepares to store a response"""
		self.question=question
		self.responses=[]

	def show_question(self):
		"""show question"""
		print(self.question)

	def store_response(self, new_response):
		"""store a new response in the system"""
		self.responses.append(new_response)

	def show_results(self):
		"""show all responses"""
		print('Responses given:')
		for responses in self.responses:
			print(f" {responses}")


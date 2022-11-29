using TMPro;
using UnityEngine;

public class QuestionManager : MonoBehaviour
{

    [SerializeField] private TMP_Text _questionTextField;
    [SerializeField] private TMP_InputField answerInputField;
    
    private string _question;
    [SerializeField] private float answer;
    
    // Start is called before the first frame update
    void Start()
    {
        GenerateQuestion();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void GenerateQuestion()
    {
        AddSubtractQuestion();

        _questionTextField.text = _question;

        ClearInputField();
    }

    void AddSubtractQuestion(int maxRange)
    {
        int operand1 = Mathf.FloorToInt(Random.Range(0, maxRange));
        int operand2 = Mathf.FloorToInt(Random.Range(0, maxRange));

        //Is it a + or - question, creates 50% chance
        if (Random.value < 0.5f)
        {
            //using string concatenation
            //_question = operand1 + "-" + operand2 + " = ? ";

            //using string interpolation
            _question = $"{operand1} - {operand2} = ?";
            answer = (operand1 - operand2);
        }
        else
        {
            //using string concatenation
            //_question = operand1 + "+" + operand2 + " = ? ";

            //using string interpolation
            _question = $"{operand1} + {operand2} = ?";
            answer = (operand1 + operand2);
        }
    }

    // This will be available outside this class
    // This will go on On End Edit, and will be called when user press enter 
    // after inputing a number
    public void ValidateAnswer()
    {
        if (answerInputField.text == answer.ToString) // cast to string to compare
        {
            GenerateQuestion();
        }
        else
        {
            ClearInputField();
        }
    }

    void ClearInputField()
    {
        //clear input field text
        answerInputField.text = "";
        answerInputField.ActivateInputField();
    }
}
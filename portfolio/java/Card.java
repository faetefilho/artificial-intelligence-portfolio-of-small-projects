package chapter_07;

public class Card 
{   // string instance variables
    private final String face;
    private final String suit;
    
    // constructor
    public Card(String cardFace, String cardSuit)
    {
        this.face = cardFace;
        this.suit = cardSuit;
    }

    // return string representing card
    // The toString method of an object is called implicitly when
    // the object is used where a string is expected
    public String toString()
    {
        return face + " of " + suit;
    }
}

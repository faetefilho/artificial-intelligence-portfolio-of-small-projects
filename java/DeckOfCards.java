package chapter_07;
import java.security.SecureRandom;

public class DeckOfCards 
{
    private static final SecureRandom randomNumbers = new SecureRandom();
    private static final int NUMBER_OF_CARDS = 52;
    
    // Declare and initialize instance variable deck, that refers to an array of cards
    // the deck array's elements are null by default, no card objects exist yet 
    private Card[] deck = new Card[NUMBER_OF_CARDS];
    private int currentCard = 0;  //index of next card to be dealt 0-51

    // constructor fills deck of cards
    public DeckOfCards()
    {
        String[] faces = {"Ace", "Deuce", "Three", "Four", "Five", "Six", 
        "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
        String[] suits = {"Hearts", "Diamonds", "Clubs", "Spades"};

        //populate card with Card objects
        for (int count = 0; count < deck.length; count++)
        {
            // initialize array of objects of type Card
            deck[count] = new Card(faces[count % 13], suits[count / 13]);
        }
    }

    //shuffle
    public void shuffle()
    {
        currentCard = 0;

        // for each Card, pick another random card (0-51) and swap them
        for (int first = 0; first < deck.length; first++)
        {
            int second = randomNumbers.nextInt(NUMBER_OF_CARDS);

            // swap current card with randomly selected Card
            Card temp = deck[first];
            deck[first] = deck[second];
            deck[second] = temp;
        }

    }

    public Card dealCard()
    {
        // determine weather Cards remain to be dealt
        if (currentCard < deck.length)
        {
            return deck[currentCard++];  //return card and increment
        }
        else
        {
            return null;  //return null to indicate all cards have been dealt
        }
    }
}

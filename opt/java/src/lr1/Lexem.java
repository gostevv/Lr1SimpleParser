package lr1;

import java.util.HashMap;
import java.util.Map;

public enum Lexem 
{
    ZERO('0'),
    ONE('1'), 
    TWO('2'), 
    THREE('3'),
    FOUR('4'), 
    FIVE('5'), 
    SIX('6'), 
    SEVEN('7'), 
    EIGHT('8'), 
    NINE('9'),
    LEFT_PARENTHESIS('('),
    RIGHT_PARENTHESIS(')'),
    MULTIPLICATION('*'),
    DIVISION('/'),
    ADDITION('+'),
    SUBTRACTION('-'),
    NUMBER,
    END((char) 0);//,
    /*WHITESPACE(' '),
    NEWLINE('\n')*/;
    
    public static Lexem valueOf(char lexemValue)
    {
        return lexemValueToLexem.get(lexemValue);
    }
        
    public static boolean isDigit(Lexem lexem)
    {
        return lexem.lexemValue >= '0' && lexem.lexemValue <= '9';
    }

    public static boolean isOperation(Lexem lexem)
    {
        return lexem.lexemValue == '*' || lexem.lexemValue == '/' || lexem.lexemValue == '+'  || lexem.lexemValue == '-';
    }
    
    public char getLexemValue()
    {
        return lexemValue;
    }
    
    private Lexem(char lexemValue)
    {
        this.lexemValue = lexemValue;
    }
    
    private Lexem()
    {
    }
    
    private char lexemValue;
    
    private static final Map<Character, Lexem> lexemValueToLexem = new HashMap<>();

    static
    {
        for (Lexem lexem : values())
        {
            lexemValueToLexem.put(lexem.lexemValue, lexem);
        }
    }
}

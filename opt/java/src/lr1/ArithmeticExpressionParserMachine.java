package lr1;

import java.util.*;

public class ArithmeticExpressionParserMachine 
{
    public ArithmeticExpressionParserMachine(int expressionLength)
    {
        this.expressionLength = expressionLength;
    }
    
    public AbstractSyntaxTree getAst()
    {
        return asts.getLast();
    }
    
    public void parse(char lexem) throws IllegalExpressionException
    {
        parsedPartOfExpressionLength++;
        current = lookahead;
        lookahead = Lexem.valueOf(lexem);
        
        if (lookahead == null)
        {
            throw new IllegalExpressionException("Unsupported kind of lexem : " + lexem);
        }

        if (current == null)
        {
            stateStack.push(new State(0, lookahead));
            lexemStack.push(null);
            astHelperList.push(-1);
        }
        else
        {
            Integer nextStateId = stateToNextStateId.get(stateStack.peek());
            List<Operation> operations = stateToOperation.get(new State(nextStateId,lookahead));
            operations = ((operations == null) ? Collections.EMPTY_LIST : operations);

            if (nextStateId == null)
            {
                throw new IllegalExpressionException("Unsupported transition.");
            }

            for (Operation operation : operations)
            {
                if (Operation.SHIFT.equals(operation))
                {
                    stateStack.push(new State(nextStateId,lookahead));
                    lexemStack.push(current);
                    astHelperList.addLast(-1);
                }
                else if (Operation.NUMBER_REDUCTION.equals(operation))
                {
                    State lastState = stateStack.peek();
                    State previousState = stateStack.peek();
                    Lexem previousLexem = lexemStack.peek();
                    while (previousState.getId() != 0 
                           && Lexem.isDigit(previousLexem))
                    {
                        stateStack.pop();
                        lexemStack.pop();
                        astHelperList.removeLast();
                        previousState = stateStack.peek();
                        previousLexem = lexemStack.peek();
                    }
                    stateStack.peek().setLookahead(Lexem.NUMBER);
                    lexemStack.push(Lexem.NUMBER);
                    astHelperList.addLast(-1);
                    stateStack.push(lastState);
                }
                else if (Operation.REDUCTION.equals(operation))
                {
                    State lastState = stateStack.peek();
                    
                    AbstractSyntaxTree ast = new AbstractSyntaxTree();
                    int pointer = astHelperList.removeLast();
                    Lexem lexemCursor = lexemStack.pop();
                    if (Lexem.NUMBER.equals(lexemCursor))
                    {
                        if (pointer > -1)
                        {
                            ast = ast.add(asts.get(pointer));
                        }
                        else
                        {
                            ast = ast.add(lexemCursor);
                        }
                    }
                    
                    State previousState = stateStack.pop();
                    while (previousState.getId() != 0)
                    {
                        previousState = stateStack.peek();
                        if (previousState.getId() != 0)
                        {
                            stateStack.pop();
                            Lexem previousLexem = lexemStack.pop();
                            pointer = astHelperList.removeLast();
                            if (Lexem.LEFT_PARENTHESIS.equals(previousLexem))
                            {
                                break;
                            }

                            if (pointer > -1)
                            {
                                ast = ast.add(asts.get(pointer));
                            }
                            else
                            {
                                ast = ast.add(previousLexem);
                            }
                            previousState = stateStack.peek();
                        }
                    }
                    stateStack.peek().setLookahead(Lexem.NUMBER);
                    lexemStack.push(Lexem.NUMBER);
                    
                    astHelperListMaxValue++;
                    astHelperList.addLast(astHelperListMaxValue);
                    
                    asts.add(ast);
                    
                    stateStack.push(lastState);
                }
            }
        }
        
        if (parsedPartOfExpressionLength == expressionLength 
            || parsedPartOfExpressionLength == expressionLength+1)
        {
            parse((char)0);
        }
    }
    
    private int expressionLength;
    private int parsedPartOfExpressionLength = 0;
    private Lexem current = null;
    private Lexem lookahead = null;
    
    private Stack<State> stateStack = new Stack<>();
    private Stack<Lexem> lexemStack = new Stack<>();
    private LinkedList<Integer> astHelperList = new LinkedList<>(); /* ast stands for abstract syntax tree */
    private LinkedList<AbstractSyntaxTree> asts = new LinkedList<>();
    private int astHelperListMaxValue = -1;
    
    private Map<State, List<Operation>> stateToOperation = new HashMap<State, List<Operation>>()
    {
        {
            List<Operation> shiftOnlyOperation = Arrays.asList(new Operation[]{Operation.SHIFT});
            List<Operation> shiftAndNumberReductionOperation = Arrays.asList(new Operation[]{Operation.SHIFT, Operation.NUMBER_REDUCTION});
            List<Operation> shiftAndReductionOperation = Arrays.asList(new Operation[]{Operation.SHIFT, Operation.REDUCTION});
            List<Operation> shiftAndReductionsOperation = Arrays.asList(new Operation[]{Operation.SHIFT, Operation.NUMBER_REDUCTION, Operation.REDUCTION});
            
            /* 0 */
            put(new State(0,Lexem.ZERO), shiftOnlyOperation);
            put(new State(0,Lexem.ONE), shiftOnlyOperation); 
            put(new State(0,Lexem.TWO), shiftOnlyOperation);
            put(new State(0,Lexem.THREE), shiftOnlyOperation);
            put(new State(0,Lexem.FOUR), shiftOnlyOperation);
            put(new State(0,Lexem.FIVE), shiftOnlyOperation);
            put(new State(0,Lexem.SIX), shiftOnlyOperation);
            put(new State(0,Lexem.SEVEN), shiftOnlyOperation);
            put(new State(0,Lexem.EIGHT), shiftOnlyOperation);
            put(new State(0,Lexem.NINE), shiftOnlyOperation);
            
            put(new State(0,Lexem.LEFT_PARENTHESIS), shiftOnlyOperation);
            
            /* 1 */
            put(new State(1,Lexem.ZERO), shiftOnlyOperation);
            put(new State(1,Lexem.ONE), shiftOnlyOperation); 
            put(new State(1,Lexem.TWO), shiftOnlyOperation);
            put(new State(1,Lexem.THREE), shiftOnlyOperation);
            put(new State(1,Lexem.FOUR), shiftOnlyOperation);
            put(new State(1,Lexem.FIVE), shiftOnlyOperation);
            put(new State(1,Lexem.SIX), shiftOnlyOperation);
            put(new State(1,Lexem.SEVEN), shiftOnlyOperation);
            put(new State(1,Lexem.EIGHT), shiftOnlyOperation);
            put(new State(1,Lexem.NINE), shiftOnlyOperation);
            
            put(new State(1,Lexem.ADDITION), shiftAndNumberReductionOperation);
            put(new State(1,Lexem.SUBTRACTION), shiftAndNumberReductionOperation);
            put(new State(1,Lexem.MULTIPLICATION), shiftAndNumberReductionOperation);
            put(new State(1,Lexem.DIVISION), shiftAndNumberReductionOperation);
            
            put(new State(1,Lexem.RIGHT_PARENTHESIS), shiftAndNumberReductionOperation);
            put(new State(1,Lexem.END), shiftAndReductionsOperation);
            
            /* 2 */
            put(new State(2,Lexem.ZERO), shiftOnlyOperation);
            put(new State(2,Lexem.ONE), shiftOnlyOperation);
            put(new State(2,Lexem.TWO), shiftOnlyOperation);
            put(new State(2,Lexem.THREE), shiftOnlyOperation);
            put(new State(2,Lexem.FOUR), shiftOnlyOperation);
            put(new State(2,Lexem.FIVE), shiftOnlyOperation);
            put(new State(2,Lexem.SIX), shiftOnlyOperation);
            put(new State(2,Lexem.SEVEN), shiftOnlyOperation);
            put(new State(2,Lexem.EIGHT), shiftOnlyOperation);
            put(new State(2,Lexem.NINE), shiftOnlyOperation);
            put(new State(2,Lexem.LEFT_PARENTHESIS), shiftOnlyOperation);
            
            /* 3 */
            put(new State(3,Lexem.ZERO), shiftOnlyOperation);
            put(new State(3,Lexem.ONE), shiftOnlyOperation);
            put(new State(3,Lexem.TWO), shiftOnlyOperation);
            put(new State(3,Lexem.THREE), shiftOnlyOperation);
            put(new State(3,Lexem.FOUR), shiftOnlyOperation);
            put(new State(3,Lexem.FIVE), shiftOnlyOperation);
            put(new State(3,Lexem.SIX), shiftOnlyOperation);
            put(new State(3,Lexem.SEVEN), shiftOnlyOperation);
            put(new State(3,Lexem.EIGHT), shiftOnlyOperation);
            put(new State(3,Lexem.NINE), shiftOnlyOperation);
            
            /* 4 */
           /* put(new State(4,Lexem.ZERO), shiftOnlyOperation);
            put(new State(4,Lexem.ONE), shiftOnlyOperation);
            put(new State(4,Lexem.TWO), shiftOnlyOperation);
            put(new State(4,Lexem.THREE), shiftOnlyOperation);
            put(new State(4,Lexem.FOUR), shiftOnlyOperation);
            put(new State(4,Lexem.FIVE), shiftOnlyOperation);
            put(new State(4,Lexem.SIX), shiftOnlyOperation);
            put(new State(4,Lexem.SEVEN), shiftOnlyOperation);
            put(new State(4,Lexem.EIGHT), shiftOnlyOperation);
            put(new State(4,Lexem.NINE), shiftOnlyOperation);*/
            
            /* 5 */
            put(new State(5,Lexem.ZERO), shiftOnlyOperation);
            put(new State(5,Lexem.ONE), shiftOnlyOperation);
            put(new State(5,Lexem.TWO), shiftOnlyOperation);
            put(new State(5,Lexem.THREE), shiftOnlyOperation);
            put(new State(5,Lexem.FOUR), shiftOnlyOperation);
            put(new State(5,Lexem.FIVE), shiftOnlyOperation);
            put(new State(5,Lexem.SIX), shiftOnlyOperation);
            put(new State(5,Lexem.SEVEN), shiftOnlyOperation);
            put(new State(5,Lexem.EIGHT), shiftOnlyOperation);
            put(new State(5,Lexem.NINE), shiftOnlyOperation);
            
            put(new State(5,Lexem.ADDITION), shiftAndReductionsOperation);
            put(new State(5,Lexem.SUBTRACTION), shiftAndReductionsOperation);
            
            put(new State(5,Lexem.MULTIPLICATION), shiftAndNumberReductionOperation);
            put(new State(5,Lexem.DIVISION), shiftAndNumberReductionOperation);
            
            put(new State(5,Lexem.RIGHT_PARENTHESIS), shiftAndNumberReductionOperation);
            put(new State(5,Lexem.LEFT_PARENTHESIS), shiftOnlyOperation);
            
            put(new State(5,Lexem.END), shiftAndReductionOperation);
            
            /* 6 */
            put(new State(6,Lexem.ADDITION), shiftAndReductionOperation);
            put(new State(6,Lexem.SUBTRACTION), shiftAndReductionOperation);
            put(new State(6,Lexem.MULTIPLICATION), shiftAndReductionOperation);
            put(new State(6,Lexem.DIVISION), shiftAndReductionOperation);
            put(new State(6,Lexem.RIGHT_PARENTHESIS), shiftAndReductionOperation);
            put(new State(6,Lexem.END), shiftAndReductionOperation);
            
            /* 7 skip */
            put(new State(7,Lexem.END), shiftAndReductionOperation);
        }
    };
    
    private Map<State, Integer> stateToNextStateId = new HashMap<State, Integer>()
    {
        {
            /* 0 - starting state */
            /* Ignore whitespaces and new lines */
//            put(new State(0,Lexem.WHITESPACE), 0);
//            put(new State(0,Lexem.NEWLINE), 0);
            
            put(new State(0,Lexem.ZERO), 1);
            put(new State(0,Lexem.ONE), 1);
            put(new State(0,Lexem.TWO), 1);
            put(new State(0,Lexem.THREE), 1);
            put(new State(0,Lexem.FOUR), 1);
            put(new State(0,Lexem.FIVE), 1);
            put(new State(0,Lexem.SIX), 1);
            put(new State(0,Lexem.SEVEN), 1);
            put(new State(0,Lexem.EIGHT), 1);
            put(new State(0,Lexem.NINE), 1);
            
            put(new State(0,Lexem.LEFT_PARENTHESIS), 2);
            
            /* 1 */
            /* Ignore whitespaces and new lines */
 //           put(new State(1,Lexem.WHITESPACE), 1);
  //          put(new State(1,Lexem.NEWLINE), 1);
            
            put(new State(1,Lexem.ZERO), 1);
            put(new State(1,Lexem.ONE), 1);
            put(new State(1,Lexem.TWO), 1);
            put(new State(1,Lexem.THREE), 1);
            put(new State(1,Lexem.FOUR), 1);
            put(new State(1,Lexem.FIVE), 1);
            put(new State(1,Lexem.SIX), 1);
            put(new State(1,Lexem.SEVEN), 1);
            put(new State(1,Lexem.EIGHT), 1);
            put(new State(1,Lexem.NINE), 1);
            
            put(new State(1,Lexem.ADDITION),3);
            put(new State(1,Lexem.SUBTRACTION),3);
            put(new State(1,Lexem.MULTIPLICATION),5);
            put(new State(1,Lexem.DIVISION),5);
            
            put(new State(1,Lexem.RIGHT_PARENTHESIS), 6);
            put(new State(1,Lexem.END), 7);
            
            /* 2 */
            /* Ignore whitespaces and new lines */
//            put(new State(2,Lexem.WHITESPACE), 2);
//            put(new State(2,Lexem.NEWLINE), 2);
            
            put(new State(2,Lexem.ZERO), 1);
            put(new State(2,Lexem.ONE), 1);
            put(new State(2,Lexem.TWO), 1);
            put(new State(2,Lexem.THREE), 1);
            put(new State(2,Lexem.FOUR), 1);
            put(new State(2,Lexem.FIVE), 1);
            put(new State(2,Lexem.SIX), 1);
            put(new State(2,Lexem.SEVEN), 1);
            put(new State(2,Lexem.EIGHT), 1);
            put(new State(2,Lexem.NINE), 1);
            put(new State(2,Lexem.LEFT_PARENTHESIS), 2);
            
            /* 3 */
            /* Ignore whitespaces and new lines */
   //         put(new State(3,Lexem.WHITESPACE), 3);
    //        put(new State(3,Lexem.NEWLINE), 3);
            
            put(new State(3,Lexem.ZERO), 1);
            put(new State(3,Lexem.ONE), 1);
            put(new State(3,Lexem.TWO), 1);
            put(new State(3,Lexem.THREE), 1);
            put(new State(3,Lexem.FOUR), 1);
            put(new State(3,Lexem.FIVE), 1);
            put(new State(3,Lexem.SIX), 1);
            put(new State(3,Lexem.SEVEN), 1);
            put(new State(3,Lexem.EIGHT), 1);
            put(new State(3,Lexem.NINE), 1);
            
            /* 4 */
            /* Ignore whitespaces and new lines */
   //         put(new State(4,Lexem.WHITESPACE), 4);
 //           put(new State(4,Lexem.NEWLINE), 4);
            
            /*put(new State(4,Lexem.ZERO), 5);
            put(new State(4,Lexem.ONE), 5);
            put(new State(4,Lexem.TWO), 5);
            put(new State(4,Lexem.THREE), 5);
            put(new State(4,Lexem.FOUR), 5);
            put(new State(4,Lexem.FIVE), 5);
            put(new State(4,Lexem.SIX), 5);
            put(new State(4,Lexem.SEVEN), 5);
            put(new State(4,Lexem.EIGHT), 5);
            put(new State(4,Lexem.NINE), 5);*/
            
            /* 5 */
            /* Ignore whitespaces and new lines */
  //          put(new State(5,Lexem.WHITESPACE), 5);
  //          put(new State(5,Lexem.NEWLINE), 5);
            
            put(new State(5,Lexem.ZERO), 5);
            put(new State(5,Lexem.ONE), 5);
            put(new State(5,Lexem.TWO), 5);
            put(new State(5,Lexem.THREE), 5);
            put(new State(5,Lexem.FOUR), 5);
            put(new State(5,Lexem.FIVE), 5);
            put(new State(5,Lexem.SIX), 5);
            put(new State(5,Lexem.SEVEN), 5);
            put(new State(5,Lexem.EIGHT), 5);
            put(new State(5,Lexem.NINE), 5);
            
            put(new State(5,Lexem.ADDITION),3);
            put(new State(5,Lexem.SUBTRACTION),3);
            put(new State(5,Lexem.MULTIPLICATION),5);
            put(new State(5,Lexem.DIVISION),5);
            
            put(new State(5,Lexem.RIGHT_PARENTHESIS), 6);
            put(new State(5,Lexem.LEFT_PARENTHESIS), 2);
            
            put(new State(5,Lexem.END), 7);
            
            /* 6 */
            /* Ignore whitespaces and new lines */
   //         put(new State(6,Lexem.WHITESPACE), 6);
  //          put(new State(6,Lexem.NEWLINE), 6);
            
            put(new State(6,Lexem.ADDITION),3);
            put(new State(6,Lexem.SUBTRACTION),3);
            put(new State(6,Lexem.MULTIPLICATION),5);
            put(new State(6,Lexem.DIVISION),5);
            put(new State(6,Lexem.RIGHT_PARENTHESIS), 6);
            put(new State(6,Lexem.END), 7);
            
            /* 7 - SUCCESS */
            /* Ignore whitespaces and new lines */
            put(new State(7,Lexem.END), 7);
   //         put(new State(7,Lexem.WHITESPACE), 7);
  //          put(new State(7,Lexem.NEWLINE), 7);            
            //put(new State(7,Lexem.NUMBER),)
        }
    };
    
    private static String reductionToNumber(String number, char nextDigitOfNumber)
    {
        StringBuilder sb = new StringBuilder(number);
        sb.append(nextDigitOfNumber);
        return sb.toString();
    }
    
    private static class State
    {
        public State(Integer id, Lexem lookahead)
        {
            this.id = id;
            this.lookahead = lookahead;
        }
        
        public Integer getId()
        {
            return id;
        }

        public void setLookahead(Lexem lookahead)
        {
            this.lookahead = lookahead;
        }

        public Lexem getLookahead()
        {
            return lookahead;
        }

        @Override
        public boolean equals(Object obj)
        {
            if (obj == null)
            {
                return false;
            }
            if (getClass() != obj.getClass())
            {
                return false;
            }
            final State other = (State) obj;
            if (!Objects.equals(this.id, other.id))
            {
                return false;
            }
            if (!Objects.equals(this.lookahead, other.lookahead))
            {
                return false;
            }
            return true;
        }

        @Override
        public int hashCode()
        {
            int hash = 5;
            hash = 13 * hash + Objects.hashCode(this.id);
            hash = 13 * hash + Objects.hashCode(this.lookahead);
            return hash;
        }
        
        private Integer id;
        private Lexem lookahead;
    }
    
    private static enum Operation
    {
        SHIFT('c'),
        REDUCTION('r'),
        NUMBER_REDUCTION('n');
        
        public static Operation valueOf(char c)
        {
            return charToOperation.get(c);
        }
        
        private Operation(char c)
        {
            this.value = c;
        }
        
        private static final Map<Character, Operation> charToOperation = new HashMap<>();

        static
        {
            for (Operation operation : values())
            {
                charToOperation.put(operation.value, operation);
            }
        }
        
        private char value;;
    }
}

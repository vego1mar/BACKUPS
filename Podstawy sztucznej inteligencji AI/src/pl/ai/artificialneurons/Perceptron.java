package pl.ai.artificialneurons;

/**
 * A basic model of a perceptron with two input data paths.
 */

public class Perceptron 
	{

	private int theta;
	private int w1;
	private int w2;
	
	
	//______________________________________________________________________________________________________________________________

	/**
	 * The instance initializer block.
	 */
	
		{
		this.theta = -4;
		this.w1 = 2;
		this.w2 = 2;
		};
	
	//______________________________________________________________________________________________________________________________
	
	/**
	 * The default constructor.
	 */
	
	public Perceptron()
		{
		super();
		};
	
	//______________________________________________________________________________________________________________________________
	
	/**
	 * Performs the learning process of the perceptron for one specified sample.
	 * @param x1 The first input data path.
	 * @param x2 The second input data path.
	 * @param d An expected value that perceptron should return for this vector data.
	 * @return <b>true</b> if wages using given sample have been modified, <b>false</b> otherwise.
	 */
	
	public boolean performLearningStep( int x1, int x2, int d )
		{	
		int sum = countSum( x1, x2 );
		int y = executeActivationFunction( sum );
		boolean wereWagesAltered = false;
		
		if ( y != d ) {
			setTheta( getTheta() + d );
			setW1( getW1() + (x1 * d) );
			setW2( getW2() + (x2 * d) );
			wereWagesAltered = true;
			}
		
		return ( wereWagesAltered );
		};
	
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Performs the learning process of the perceptron using fixed set of data for the minimal number of epochs.
	 * The altered wages are stored in fields.
	 * @return The number of learning epochs that was needed to learn the perceptron returning the correct data values.
	 */
	
	public int performLearningProcess()
		{
		int x1[] = {  2,  2,  0,  -2,  -2,   0,    4  };
		int x2[] = {  1,  2,  6,  10,   0,   0,  -20  };
		int d[] =  {  1,  1,  1,  -1,  -1,  -1,   -1  };
		boolean currentEpochResults[] = new boolean[ x1.length ];
		boolean isOutputIncorrect = true;
		boolean isLearningFinished = true;
		int numberOfEpochs = 0;
		int y = 0;
		int i;
		
		while ( isOutputIncorrect ) {
			// Modify wages if necessary.
			for ( i=0; i<x1.length; i++ ) {
				performLearningStep( x1[i], x2[i], d[i] );
				}
			
			// Check the results for the whole epoch.
			for ( i=0; i<x2.length; i++ ) {
				y = getResult( x1[i], x2[i] );
				
				if ( y == d[i] ) {
					currentEpochResults[i] = true;
					}				
				}
			
			numberOfEpochs++;
			isLearningFinished = true;
			
			// Check whether learning should end.
			for ( i=0; i<currentEpochResults.length; i++ ) {
				isLearningFinished = isLearningFinished && currentEpochResults[i];
				currentEpochResults[i] = false;
				}
			
			isOutputIncorrect = !isLearningFinished;
			}
		
		return ( numberOfEpochs );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Counts the sum of the perceptron from the given data.
	 * @param x1 The first input data path.
	 * @param x2 The second input data path.
	 * @return Series value of the perceptron.
	 */
		
	private int countSum( int x1, int x2 )
		{
		return ( getTheta() + (x1 * getW1()) + (x2 * getW2()) );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * An activation function used in the learning process.
	 * @param sum The sum received from the perceptron.
	 * @return sign( sum ). <b>1</b> if the sum is greater than 0, <b>-1</b> otherwise.
	 */
		
	private int executeActivationFunction( int sum )
		{
		return ( ( sum > 0 ) ? ( 1 ) : ( -1 ) );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Counts the output of the perceptron from the given data.
	 * @param x1 The first input data path.
	 * @param x2 The second input data path.
	 * @return sign( series[x1,x2] ), that is <b>1</b> or <b>-1</b>.
	 */
		
	public int getResult( int x1, int x2 )
		{
		return ( executeActivationFunction( countSum( x1, x2 ) ) );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Getter.
	 * @return The current value of the <em>theta</em> field (the bias).
	 */
		
	public int getTheta()
		{
		return ( this.theta );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Setter.
	 * @param theta A new value of the <em>theta</em> field (the new bias, <em>w0</em>).
	 */
		
	public void setTheta( int theta )
		{
		this.theta = theta;
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Getter.
	 * @return The first input data path (<em>w1</em> field).
	 */
		
	public int getW1()
		{
		return ( this.w1 );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Setter.
	 * @param w1 A new value of the first input data path (<em>w1</em> field).
	 */
		
	public void setW1( int w1 )
		{
		this.w1 = w1;
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Getter.
	 * @return The second input data path (<em>w2</em> field).
	 */
		
	public int getW2()
		{
		return ( this.w2 );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Setter.
	 * @param w2 A new value of the second input data path (<em>w2</em> field).
	 */
		
	public void setW2( int w2 )
		{
		this.w2 = w2;
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Test code.
	 * @param args No use.
	 */
		
	public static void main( String[] args )
		{
		Perceptron p = new Perceptron();
		int numberOfLearningEpochs = p.performLearningProcess();
		
		System.out.println( "Perceptron learned after " + numberOfLearningEpochs + " epoch(s)." );
		System.out.println();
		System.out.println( "w0 = " + p.getTheta() );
		System.out.println( "w1 = " + p.getW1() );
		System.out.println( "w2 = " + p.getW2() );
		System.out.println();
		System.out.println( "f(  2,  1 ) = " + p.getResult(  2,  1 ) );
		System.out.println( "f(  2,  2 ) = " + p.getResult(  2,  2 ) );
		System.out.println( "f(  0,  6 ) = " + p.getResult(  0,  6 ) );
		System.out.println( "f( -2, 10 ) = " + p.getResult( -2, 10 ) );
		System.out.println( "f( -2,  0 ) = " + p.getResult( -2,  0 ) );
		System.out.println( "f(  0,  0 ) = " + p.getResult(  0,  0 ) );
		System.out.println( "f(  4,-20 ) = " + p.getResult(  4,-20 ) );
		};
		
	//______________________________________________________________________________________________________________________________
	
	};

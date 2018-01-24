package pl.ai.artificialneurons;

/** 
 * A model of a Hebb's perceptron (artificial neuron) with the vector of WAGES_VECTOR_SIZE number input data paths.
 * This is a version <span style="text-decoration:underline";>with</span> a teacher.
 */

public final class HebbNeuron 
	{

	public final static int WAGES_VECTOR_SIZE = 13;
	
	private double wages[];
	private double learningFactor;
	private double activationFunctionFactor;
	private double learningErrorCoefficient;
	
	
	//______________________________________________________________________________________________________________________________
	
	/**
	 * The instance initializer block.
	 */
	
		{
		this.wages = new double[ WAGES_VECTOR_SIZE ];
		this.learningFactor = 0.2;
		this.activationFunctionFactor = 0.8;
		this.learningErrorCoefficient = 0.009;
		};
	
	//______________________________________________________________________________________________________________________________
	
	/**
	 * The default constructor. Determines a set of pseudo-random numbers to the wages vector.
	 */
	
	public HebbNeuron()
		{
		super();
		assignNewRandomWages();
		this.wages[0] = 1.0;
		};
	
	//______________________________________________________________________________________________________________________________
	
	/**
	 * Performs the learning process of the Hebb's neuron for one specified epoch.
	 * @param x A vector of the input data path.
	 * @param d An expected value that Hebb's neuron should return for this vector data.
	 * @return An error value for the specified pattern (sample).
	 */
	
	public double performLearningStep( int[] x, int d )
		{
		double sum = countSum( x );
		double y = executeActivationFunction( sum );
			
		for ( int i=0; i<WAGES_VECTOR_SIZE; i++ ) {
			this.wages[i] = this.wages[i] + (this.learningFactor * x[i] * d);
			}

		return ( 0.5 * (y - d) * (y - d) );
		};
	
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Performs the learning process of the Hebb's neuron using fixed set of data.
	 * After completed, the neuron will be able to recognize digit '1' and '4'.
	 * @return The number of learning epochs that was needed to learn the Hebb's neuron of returning the correct data values.
	 */
	
	public int performLearningProcess()
		{
		int digit1[] = { 1, -1, -1,  1, -1, -1,  1, -1, -1,  1, -1, -1,  1 };
		int digit4[] = { 1,  1, -1,  1,  1,  1,  1, -1, -1,  1, -1, -1,  1 };
		int d[] =  { -1,  1 };
		int numberOfEpochs = 0;
		double error = 0.0;
		double acceptableError = getLearningErrorCoefficient();
		
		do {
			error = performLearningStep( digit1, d[0] );
			error += performLearningStep( digit4, d[1] );
			numberOfEpochs++;
			}
		while ( error > acceptableError );
		
		return ( numberOfEpochs );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Counts the sum of the Hebb's neuron from the given data.
	 * @param x A vector of the input data path.
	 * @return Series value of the Hebb's neuron.
	 * @throws IllegalArgumentException while the passed vector size is not equal with the vector of wages size.
	 */
		
	private double countSum( int[] x )
		{
		if ( x.length != WAGES_VECTOR_SIZE ) {
			throw ( new IllegalArgumentException( "Vector has no the same size as the vector of wages." ) );
			}
		
		double sum = 0;
		
		for ( int i=0; i<x.length; i++ ) {
			sum += x[i] * this.wages[i];
			}
		
		return ( sum );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * A sigmoidal bipolar activation function used in the learning process.
	 * @param sum The sum received from the Hebb's neuron.
	 * @return sigmoidal_bipolar( sum ).
	 */
		
	private double executeActivationFunction( double sum )
		{
		double exponent = Math.exp( -(this.activationFunctionFactor) * sum );
		return ( (1 - exponent) / (1 + exponent) );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Counts the output of the Hebb's neuron from the given data.
	 * @param x A vector of the input data path.
	 * @return sigmoidal_bipolar( series[x] ).
	 */
		
	public double getResult( int[] x )
		{
		return ( executeActivationFunction( countSum( x ) ) );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Assigns new values to the vector of wages that will be a pseudo-random numbers from an interval of [0;1).
	 */
		
	public void assignNewRandomWages()
		{
		java.util.Random r = new java.util.Random( System.currentTimeMillis() );
		
		for ( int i=0; i<WAGES_VECTOR_SIZE; i++ ) {
			this.wages[i] = r.nextDouble();
			}
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Getter.
	 * @return The current value of the learning factor (ni).
	 */
		
	public double getLearningFactor()
		{
		return ( this.learningFactor );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Setter.
	 * @param newLearningFactor A new value of the learning factor (ni).
	 */
		
	public void setLearningFactor( double newLearningFactor )
		{
		this.learningFactor = newLearningFactor;
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Getter.
	 * @return The current value of the wages vector.
	 */
		
	public double[] getWages()
		{
		return ( this.wages );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Setter.
	 * @param newWages A new value of the wages vector.
	 * @throws IllegalArgumentException while the passed vector size is not equal with the vector of wages size.
	 */
		
	public void setWages( double[] newWages )
		{
		if ( newWages.length != WAGES_VECTOR_SIZE ) {
			throw ( new IllegalArgumentException( "Vector has an improper size. The expected is " + WAGES_VECTOR_SIZE ) );
			}
		
		for ( int i=0; i<WAGES_VECTOR_SIZE; i++ ) {
			this.wages[i] = newWages[i];
			}
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Setter.
	 * @param newCoefficient A new value of the activation function factor (beta).
	 */
		
	public void setActivationFunctionFactor( double newFactor )
		{
		this.activationFunctionFactor = newFactor;
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Getter.
	 * @return The current value of the activation function factor (beta).
	 */
		
	public double getActivationFunctionFactor()
		{
		return ( this.activationFunctionFactor );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Setter.
	 * @param newCoefficient A new value of the learning error coefficient (of acceptance).
	 */
		
	public void setLearningErrorCoefficient( double newCoefficient )
		{
		this.learningErrorCoefficient = newCoefficient;
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Getter.
	 * @return The current value of the learning error coefficient (of acceptance).
	 */
		
	public double getLearningErrorCoefficient()
		{
		return ( this.learningErrorCoefficient );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Test code.
	 * @param args No use.
	 */
		
	public static void main( String[] args )
		{
		try {
			double[] wages = new double [ HebbNeuron.WAGES_VECTOR_SIZE ];
			HebbNeuron hebb = new HebbNeuron();
			hebb.setWages( wages );
			hebb.setLearningFactor( 1.0 );
			hebb.setActivationFunctionFactor( 1.0 );
			hebb.setLearningErrorCoefficient( 0.001 );
			
			System.out.println( "Hebb neuron learned after " + hebb.performLearningProcess() + " epoch(s)." );
			System.out.println();
			java.util.Locale locale = new java.util.Locale( "en", "US" );
			System.out.println( "learning factor  = " + String.format( locale, "%9.3f", hebb.getLearningFactor() ) );
			System.out.println( "acceptable error = " + String.format( locale, "%9.3f", hebb.getLearningErrorCoefficient() ) );
			System.out.println( "beta             = " + String.format( locale, "%9.3f", hebb.getActivationFunctionFactor() ) );
			System.out.println();
			System.out.print( "wages = [ " );
			
			for ( double wage : hebb.getWages() ) {
				System.out.print( String.format( locale , "%.2f", wage ) + "; " );
				}
			
			System.out.println( "]" );
			System.out.println();
			int[] digit1 = { 1, -1, -1,  1, -1, -1,  1, -1, -1,  1, -1, -1,  1 };
			int[] digit4 = { 1,  1, -1,  1,  1,  1,  1, -1, -1,  1, -1, -1,  1 };
			System.out.println( "f(digit1) = " + String.format( locale, "%.2f", hebb.getResult( digit1 ) ) );
			System.out.println( "f(digit4) = " + String.format( locale, "%.2f", hebb.getResult( digit4 ) ) );
			System.out.println();		
			digit1 = new int[] { 1, -1, -1,  1, -1, -1,  1, -1,  1,  1, -1, -1,  1 };
			digit4 = new int[] { 1,  1,  1,  1,  1,  1,  1, -1, -1,  1, -1, -1,  1 };
			System.out.println( "f(digit1 + noise) = " + String.format( locale, "%.2f", hebb.getResult( digit1 ) ) );
			System.out.println( "f(digit4 + noise) = " + String.format( locale, "%.2f", hebb.getResult( digit4 ) ) );
			}
		catch ( java.util.IllegalFormatException x ) {
			x.printStackTrace();
			}		
		catch ( IllegalArgumentException x ) {		
			x.printStackTrace();
			}
		catch ( NullPointerException x ) {
			x.printStackTrace();
			}
		catch ( Exception x ) {
			x.printStackTrace();
			}		
		};
		
	//______________________________________________________________________________________________________________________________
	
	};

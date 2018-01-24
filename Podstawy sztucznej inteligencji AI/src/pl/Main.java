package pl;

import pl.ai.artificialneurons.Perceptron;
import pl.ai.artificialneurons.HebbNeuron;

import java.util.Locale;

/**
 * A class for testing other classes.
 */

public class Main 
	{

	//______________________________________________________________________________________________________________________________
	
	/**
	 * Main testing function.
	 * @param args No use.
	 */
	
	public static void main( String[] args )
		{
		System.out.println( "=====================================================================================" );
		testBasicPerceptron();
		System.out.println();
		
		System.out.println( "=====================================================================================" );
		testHebbNeuronWithTwoPatternsRecognition();
		System.out.println();
		
		System.out.println( "=====================================================================================" );
		testHebbNeuronWithThreePatternsRecognition();
		System.out.println();
		};
	
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Exercise 6. A perceptron classifying points on the coordinate system terms of some straight line y=ax+b.
	 */
		
	private static void testBasicPerceptron()
		{
		Perceptron.main( null );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Exercise 7. A Hebb's neuron learned to recognize digit '1' and '4' using the sigmoidal bipolar activation function.
	 */
		
	private static void testHebbNeuronWithTwoPatternsRecognition()
		{
		HebbNeuron.main( null );
		};
	
	//______________________________________________________________________________________________________________________________
	
	/**
	 * Exercise 8. An extended version of exercise 7.
	 * Hebb's neuron is learned to recognize digit '1' and '4' as well as digit '7' using the sigmoidal bipolar activation function.
	 */
		
	private static void testHebbNeuronWithThreePatternsRecognition()
		{
		try {
			HebbNeuron neuron1 = new HebbNeuron();
			HebbNeuron neuron2 = new HebbNeuron();
			
			Locale locale = new Locale( "en", "US" );
			
			double[] wages = new double [ HebbNeuron.WAGES_VECTOR_SIZE ];
			wages[0] = 1.0;
			neuron1.setWages( wages );
			neuron2.setWages( wages );

			int digit1[] = { 1, -1, -1,  1, -1, -1,  1, -1, -1,  1, -1, -1,  1 };
			int digit4[] = { 1,  1, -1,  1,  1,  1,  1, -1, -1,  1, -1, -1,  1 };
			int digit7[] = { 1,  1,  1,  1, -1, -1,  1, -1, -1,  1, -1, -1,  1 };

			int numberOfEpochs = 0;
			double error;
			double acceptableError = neuron1.getLearningErrorCoefficient();
			
			do {
				error  = repeatUntilThresholdIsNotReached( acceptableError, neuron1, digit1,  1 );
				error += repeatUntilThresholdIsNotReached( acceptableError, neuron2, digit1,  1 );
				error += repeatUntilThresholdIsNotReached( acceptableError, neuron1, digit4, -1 );
				error += repeatUntilThresholdIsNotReached( acceptableError, neuron2, digit4, -1 );
				error += repeatUntilThresholdIsNotReached( acceptableError, neuron1, digit7, -1 );
				error += repeatUntilThresholdIsNotReached( acceptableError, neuron2, digit7,  1 );
				numberOfEpochs++;
				}
			while ( error > acceptableError );
			
			System.out.println( "Net learned after " + numberOfEpochs + " epoch(s)." + System.lineSeparator() );
			printLearningResults( locale, neuron1, neuron2, digit1, digit4, digit7 );
			printHebbNeuronData( locale, neuron1 );
			printHebbNeuronData( locale, neuron2 );
			System.out.println();
			printResultsForNoisedPatterns( locale, neuron1, neuron2 );
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
		
	/**
	 * Appendix A to exercise 8. Repeats learning of the specified Hebb's neuron until the threshold (the acceptable error) is reached.
	 * @param acceptableError A learning error of acceptance.
	 * @param neuron A Hebb's neuron to perform operation on.
	 * @param digit A vector of data input path (a pattern to recognize).
	 * @param d An expected value of vector recognition.
	 * @return The error for this learning cycle step.
	 */
		
	private static double repeatUntilThresholdIsNotReached( double acceptableError, HebbNeuron neuron, int[] digit, int d )
		{
		double localError;
		
		do {
			localError = neuron.performLearningStep( digit, d );
			}
		while ( localError > acceptableError );
		
		return ( localError );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Appendix B to exercise 8. Prints to the standard output the results of the net learning.
	 * @param locale A localization set of data to indicate floating-point numbers representation of I18N feature.
	 * @param neuron1 The first Hebb's neuron of the net.
	 * @param neuron2 The second Hebb's neuron of the net.
	 * @param digit1 A pattern definition of a digit '1'.
	 * @param digit4 A pattern definition of a digit '4'.
	 * @param digit7 A pattern definition of a digit '7'.
	 */
		
	private static void printLearningResults( Locale locale, HebbNeuron neuron1, HebbNeuron neuron2, int[] digit1, int[] digit4, int[] digit7 )
		{
		System.out.println( "f(neuron1,digit1) = " + String.format( locale, "% .2f", neuron1.getResult( digit1 ) ) );
		System.out.println( "f(neuron2,digit1) = " + String.format( locale, "% .2f", neuron2.getResult( digit1 ) ) );
		System.out.println( "f(neuron1,digit4) = " + String.format( locale, "% .2f", neuron1.getResult( digit4 ) ) );
		System.out.println( "f(neuron2,digit4) = " + String.format( locale, "% .2f", neuron2.getResult( digit4 ) ) );
		System.out.println( "f(neuron1,digit7) = " + String.format( locale, "% .2f", neuron1.getResult( digit7 ) ) );
		System.out.println( "f(neuron2,digit7) = " + String.format( locale, "% .2f", neuron2.getResult( digit7 ) ) );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Appendix C to exercise 8. Prints to the standard output the start data set of a specified Hebb neuron.
	 * @param locale A localization set of data to indicate floating-point numbers representation of I18N feature.
	 * @param neuron The Hebb's neuron to perform operation on.
	 */
		
	private static void printHebbNeuronData( Locale locale, HebbNeuron neuron )
		{
		System.out.println();
		System.out.println( "learning factor  = " + String.format( locale, "%9.3f", neuron.getLearningFactor() ) );
		System.out.println( "acceptable error = " + String.format( locale, "%9.3f", neuron.getLearningErrorCoefficient() ) );
		System.out.println( "beta             = " + String.format( locale, "%9.3f", neuron.getActivationFunctionFactor() ) );
		System.out.print( "wages = [ " );
		
		for ( double wage : neuron.getWages() ) {
			System.out.print( String.format( locale , "%.2f", wage ) + "; " );
			}
		
		System.out.println( "]" );
		};
		
	//______________________________________________________________________________________________________________________________
		
	/**
	 * Appendix D to exercise 8. Prints to the standard output the results returned by the net for the noised patterns.
	 * @param locale A localization set of data to indicate floating-point numbers representation of I18N feature.
	 * @param neuron1 The first Hebb's neuron of the net.
	 * @param neuron2 The second Hebb's neuron of the net.
	 */
		
	private static void printResultsForNoisedPatterns( Locale locale, HebbNeuron neuron1, HebbNeuron neuron2 )
		{
		int[] digit1 = new int[] { 1, -1, -1,  1, -1, -1,  1, -1,  1,  1, -1, -1,  1 };
		int[] digit4 = new int[] { 1,  1,  1,  1,  1,  1,  1, -1, -1,  1, -1, -1,  1 };
		int[] digit7 = new int[] { 1,  1,  1,  1, -1, -1,  1, -1,  1,  1, -1, -1,  1 };
		
		System.out.println( "Noised patterns:" );
		printLearningResults( locale, neuron1, neuron2, digit1, digit4, digit7 );
		};
		
	//______________________________________________________________________________________________________________________________
	
	};
	

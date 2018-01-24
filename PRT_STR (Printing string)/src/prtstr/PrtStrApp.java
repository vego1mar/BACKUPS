package prtstr;

import java.awt.Dimension;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import net.miginfocom.swing.MigLayout;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.border.EtchedBorder;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.SwingConstants;
import javax.swing.JTabbedPane;
import javax.swing.JScrollPane;
import java.awt.AWTException;
import java.awt.BorderLayout;
import java.awt.CardLayout;
import javax.swing.ScrollPaneConstants;
import javax.swing.SpinnerNumberModel;
import javax.swing.JTextArea;
import java.awt.Font;
import java.awt.Frame;
import java.awt.HeadlessException;
import java.awt.MenuItem;
import java.awt.PopupMenu;
import java.awt.SystemTray;
import java.awt.Toolkit;
import java.awt.TrayIcon;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Color;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.MissingResourceException;
import java.util.ResourceBundle;
import java.util.Scanner;
import javax.swing.Timer;
import javax.swing.UIManager;
import java.util.TreeMap;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.regex.Pattern;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.InputEvent;
import java.awt.Cursor;
import java.awt.Dialog;
import javax.swing.JSeparator;
import javax.swing.JSpinner;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import javax.swing.JMenuBar;
import javax.swing.JMenu;


/**********************************************************************************************
 * PrtStrApp <br>
 * Printing string application <br>
 * <br>
 * Parsing some strings of separated numbers. Outputs related strings to use it in
 * printing on a printer in odd-even way with altered 'page per sheet' feature.
 * <br>
 * @version 1.0, X 2016 (not sealed) <p>
 * @author Black Sun<p>
 *********************************************************************************************/

public class PrtStrApp 
	{
	
	// ============================ FRAME COMPONENTS ============================ //
	private JFrame frame;
	
	private JPanel leftPanel;
	private JLabel startPageLabel;
	private JTextField startPageTextField;
	private JLabel endPageLabel;
	private JTextField endPageTextField;
	private JLabel pagesPerSheetLabel;
	private JComboBox<String> pagesPerSheetComboBox;
	private JButton proceedButton;
	private JSeparator separatorAfterProceedButton;
	private JButton clearLogButton;
	private JLabel statusLabel;
	private JButton precautionsButton;

	private JPanel rightPanel;
	private JTabbedPane tabbedPane;
	private JScrollPane logTabScrollPane;
	private JTextArea logTabTextArea;
	private JLabel outputTabPagesToMiss;
	private JLabel outputTabOutputLabel;
	private JScrollPane pagesToMissScrollPane;
	private JScrollPane outputScrollPane;
	private JTextArea pagesToMissTextArea;
	private JTextArea outputTextArea;
	
	
	// ============================ TIMER ============================ //
	private Timer timer;
	private long startTime;
	private long currentTime;
	private long elapsedSeconds;
	private long elapsedMinutes;
	
	
	// ============================ INTERNATIONALIZATION ============================ //
	private Locale locale;
	private ResourceBundle rcBundle;
	private JComboBox<String> languageComboBox;
	
	
	// ============================ SYSTEM TRAY COMPONENTS ============================ //
	private TrayIcon trayIcon;
	
	
	// ============================ MENU BAR LISTS ============================ //
	private JMenuBar menuBar;
	
	private JMenu programMenu;
	private JMenuItem tryToRestartMenuItem;
	private JMenuItem getStackTraceMenuItem;
	private JMenuItem exitMenuItem;
	
	private JMenu aboutMenu;
	private JMenuItem informationMenuItem;
	
	private JMenu customizeMenu;
	private JMenuItem propertiesOfUIManagerMenuItem;
	
	
	
	//_________________________________________________________________________________________________________________________________________________________
	
	/**
	 * An entry point for this application with graphical interface. <br>
	 * @param args No use.<p>
	 * @since 1.0 <p>
	 * @wbp.parser.entryPoint A comment annotation for WindowBuilder Editor plug-in of Eclipse IDE. <p>
	 */
	
	public static void main( String[] args ) 
		{
		SwingUtilities.invokeLater( new Runnable() {
			@Override
			public void run()
				{
				new PrtStrApp().runGUI();
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * The instance initializer block. <br><br>Used to initialize and define timer's behavior.<br>
	 * Used to set the UIManager message font for JOptionPane at the application start.<br>
	 * Used for I18N Java programming language feature.<br>
	 * @since 1.0 <p>
	 */
		
		{
		//javax.swing.UIManager.put("OptionPane.messageFont", new Font("System", Font.PLAIN, 12));
		this.elapsedMinutes = 0L;
			
		this.timer = new Timer(1_000,new ActionListener() {
			@Override
			public void actionPerformed( ActionEvent event ) {
				PrtStrApp.this.currentTime = System.currentTimeMillis();
				PrtStrApp.this.elapsedSeconds = ((PrtStrApp.this.currentTime - PrtStrApp.this.startTime) / 1_000) % 60;
				PrtStrApp.this.statusLabel.setText( String.format("%02d",PrtStrApp.this.elapsedMinutes) + ":" + String.format("%02d",PrtStrApp.this.elapsedSeconds) );
				if ( PrtStrApp.this.elapsedSeconds >= 59 ) { PrtStrApp.this.elapsedMinutes++; }
				}
			});
		
		this.locale = new Locale("pl","PL");
		
		SwingUtilities.invokeLater( new Runnable() {
			@Override
			public void run() {
				UIManager.put("OptionPane.yesButtonText", PrtStrApp.this.rcBundle.getString("yesButtonText"));
				UIManager.put("OptionPane.noButtonText", PrtStrApp.this.rcBundle.getString("noButtonText"));
				UIManager.put("OptionPane.cancelButtonText", PrtStrApp.this.rcBundle.getString("cancelButtonText"));
				UIManager.put("OptionPane.titleButtonText", PrtStrApp.this.rcBundle.getString("titleButtonText"));
				}
			});
		
		try {
			this.rcBundle = ResourceBundle.getBundle("PrtStrAppLocale",this.locale);
			}
		catch ( NullPointerException | MissingResourceException x ) {
			String msg = "An exception was thrown during an initialization of the ResourceBundle.<br><br>";
			String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
			String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
			String errMsg = "NullPointerException | MissingResourceException<br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
			String htmlMessage = "<html>" + msg + errMsg + "</html>";
			JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Accessing ResourceBundle problem", JOptionPane.ERROR_MESSAGE, null);
			}
		}
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Executes the Swing GUI of this application. <br>
	 * @since 1.0 <p>
	 */
		
	private void runGUI()
		{
		//JFrame.setDefaultLookAndFeelDecorated( true );
		
		// Defining the main window.
		this.frame = new JFrame( this.rcBundle.getString("frameName") );
		this.frame.setSize( new Dimension(860,480) );
		this.frame.setPreferredSize( new Dimension(860,480) );
		this.frame.setResizable( false );
		//this.frame.setDefaultCloseOperation( JFrame.DISPOSE_ON_CLOSE );
		this.frame.setDefaultCloseOperation( JFrame.DO_NOTHING_ON_CLOSE );
		this.frame.getContentPane().setLayout( new MigLayout("", "[][]", "[grow]") );
		
		// Calling the creators.
		this.defineLeftPanel();
		this.defineRightPanel();
		this.defineFrameListener();
		this.defineMenuBar();
		
		// Finishing the stub.
		this.frame.pack();
		this.frame.setLocationRelativeTo( null );
		this.frame.setVisible( true );
		
		// Running the time counter.
		this.startTime = System.currentTimeMillis();
		this.timer.start();
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define the left panel of the main window. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineLeftPanel()
		{
		// Defining the left panel itself.
		this.leftPanel = new JPanel();
		this.leftPanel.setBorder( BorderFactory.createEtchedBorder(EtchedBorder.LOWERED, null, null) );
		this.leftPanel.setMinimumSize( new Dimension(270, 300) );
		this.leftPanel.setPreferredSize( new Dimension(270, 300) );
		this.frame.getContentPane().add(leftPanel, "cell 0 0,west");
		this.leftPanel.setLayout(new MigLayout("", "[][][][grow,center][5px:n,right]", "[15px:n][][][7px:n][][7px:n][][15px:n][][15px:n][][190px:n]"));
		
		// Calling the creators.
		this.defineStartPageComponents();
		this.defineEndPageComponents();
		this.definePagesPerSheetComponents();
		this.defineProceedButton();
		this.defineSeparatorAfterProceedButton();
		this.defineClearLogButton();
		this.defineStatusLabel();
		this.definePrecautionsButton();
		this.defineLanguageComboBox();
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define 'start page' components (label, text field) on the left panel of the main window. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineStartPageComponents()
		{
		// Defining the 'start page' text field for user input.
		this.startPageTextField = new JTextField();
		this.startPageTextField.setHorizontalAlignment( SwingConstants.LEFT );
		this.startPageTextField.setForeground( Color.BLACK );
		this.leftPanel.add(this.startPageTextField, "cell 3 1,growx");
		this.startPageTextField.setColumns( 10 );
		
		// Defining the 'start page' label.
		//this.startPageLabel = new JLabel("Start page:");
		this.startPageLabel = new JLabel( this.rcBundle.getString("startPageLabel") );
		this.leftPanel.add(this.startPageLabel, "cell 1 1,alignx trailing");
		
		// Defining mouse action.
		this.startPageTextField.addMouseListener( new MouseAdapter() {
			@Override
			public void mouseClicked( MouseEvent mouseEvent ) 
				{
				PrtStrApp.this.startPageTextField.setForeground( Color.BLACK );
				PrtStrApp.this.endPageTextField.setForeground( Color.BLACK );
				}
			});
		
		// Defining focus action.
		this.startPageTextField.addFocusListener( new FocusAdapter() {
			@Override
			public void focusGained( FocusEvent focusEvent ) 
				{
				PrtStrApp.this.startPageTextField.setForeground( Color.BLACK );
				PrtStrApp.this.endPageTextField.setForeground( Color.BLACK );
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define 'end page' components (label, text field) on the left panel of the main window. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineEndPageComponents()
		{
		// Defining the 'end page' text field for user input.
		this.endPageTextField = new JTextField();
		this.endPageTextField.setHorizontalAlignment( SwingConstants.LEFT );
		this.endPageTextField.setForeground( Color.BLACK );
		this.leftPanel.add(this.endPageTextField, "cell 3 2,growx");
		this.endPageTextField.setColumns( 10 );
		
		// Defining the 'end page' label.
		this.endPageLabel = new JLabel( this.rcBundle.getString("endPageLabel") );
		this.leftPanel.add(this.endPageLabel, "cell 1 2,alignx trailing");
		
		// Defining mouse action.
		this.endPageTextField.addMouseListener( new MouseAdapter() {
			@Override
			public void mouseClicked( MouseEvent mouseEvent ) 
				{
				PrtStrApp.this.endPageTextField.setForeground( Color.BLACK );
				PrtStrApp.this.startPageTextField.setForeground( Color.BLACK );
				}
			});
		
		// Defining focus action.
		this.endPageTextField.addFocusListener( new FocusAdapter() {
			@Override
			public void focusGained( FocusEvent focusEvent ) 
				{
				PrtStrApp.this.endPageTextField.setForeground( Color.BLACK );
				PrtStrApp.this.startPageTextField.setForeground( Color.BLACK );
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define 'pages per sheet' components (label, combo box) on the left panel of the main window. <br>
	 * @since 1.0 <p>
	 */
		
	private void definePagesPerSheetComponents()
		{
		// Defining the 'pages per sheet' label.
		this.pagesPerSheetLabel = new JLabel( this.rcBundle.getString("pagesPerSheetLabel") );
		this.leftPanel.add(this.pagesPerSheetLabel, "cell 1 4,alignx trailing");
		
		// Defining the 'pages per sheet' combo box.
		String [] comboBoxValues = new String [] {"1","2","4","6","9","16"};
		this.pagesPerSheetComboBox = new JComboBox( comboBoxValues ); // !!!
		//this.pagesPerSheetComboBox = new JComboBox<String>( comboBoxValues );
		this.pagesPerSheetComboBox.setSelectedIndex( 2 );
		this.leftPanel.add(this.pagesPerSheetComboBox, "cell 3 4,growx");
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define 'proceed' button on the left panel of the main window. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineProceedButton()
		{
		// Defining button's properties.
		this.proceedButton = new JButton( this.rcBundle.getString("proceedButton") );
		this.proceedButton.setMinimumSize( new Dimension(135, 23) );
		this.proceedButton.setPreferredSize( new Dimension(135, 23) );
		this.leftPanel.add(this.proceedButton, "cell 3 6,growx,aligny center");
		
		// Defining action.
		this.proceedButton.addActionListener( new ActionListener() {
			@Override
			public void actionPerformed( ActionEvent actionEvent ) 
				{
				AtomicInteger startPage = new AtomicInteger( 0 );
				AtomicInteger endPage = new AtomicInteger( 0 );
				boolean correct = PrtStrApp.this.checkStartAndEndPageTextFieldsValuesBeforeParsing(startPage, endPage);
				AtomicInteger numberOfPagesCuttedOff = new AtomicInteger( 0 );
				
				if ( correct == true )
					{
					LinkedList<Integer> individualPages = new LinkedList<Integer>();
					TreeMap<Integer,Integer> rangedPages = new TreeMap<Integer,Integer>();
					ArrayList<Integer> outputPages = new ArrayList<Integer>();
					String[] resultString = null;
					
					PrtStrApp.this.parsePagesToMissTextAreaContent( individualPages, rangedPages, numberOfPagesCuttedOff, startPage.get(), endPage.get() );
					PrtStrApp.this.processIndividualAndRangedPagesCollections( individualPages, rangedPages, startPage, endPage, outputPages );
					resultString = PrtStrApp.this.groupByOddAndEvenPairs( outputPages );
					
					double loadFactor = PrtStrApp.this.countLoadFactor( numberOfPagesCuttedOff.get() );
					String message = String.format( "%.2f pages", loadFactor ) + System.lineSeparator() + String.format("%.2f sheets", loadFactor / 2.0);
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, message, "Load factor", JOptionPane.INFORMATION_MESSAGE );
					
					// Logging the results.
					PrtStrApp.this.logTabTextArea.append(
						"Request: {"
						+ " startPage = \u00BB" + PrtStrApp.this.startPageTextField.getText().intern() + "\u00AB,"
						+ " endPage = \u00BB" + PrtStrApp.this.endPageTextField.getText().intern() + "\u00AB,"
						+ " pagesPerSheet = \u00BB" + PrtStrApp.this.pagesPerSheetComboBox.getSelectedItem().toString().intern() + "\u00AB,"
						+ " pagesToMiss = \u00BB" + PrtStrApp.this.pagesToMissTextArea.getText().intern() + "\u00AB"
						+ " }." + System.getProperty("line.separator").intern() +
						"Answer: { \u00BBodd: " + resultString[0] + " even: " + resultString[1] + "\u00AB }"
						+ System.lineSeparator().intern()
						);
					}
				else
					{
					// Changing the color of 'start' and 'end' page text field's to red. 
					String str = PrtStrApp.this.startPageTextField.getText().intern();
					PrtStrApp.this.startPageTextField.setForeground( Color.RED );
					PrtStrApp.this.startPageTextField.setText( str );
					str = PrtStrApp.this.endPageTextField.getText().intern();
					PrtStrApp.this.endPageTextField.setForeground( Color.RED );
					PrtStrApp.this.endPageTextField.setText( str );
					}
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define a separator in the left panel after the 'proceed' button. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineSeparatorAfterProceedButton()
		{
		this.separatorAfterProceedButton = new JSeparator();
		this.separatorAfterProceedButton.setPreferredSize( new Dimension(240,1) );
		this.separatorAfterProceedButton.setSize( new Dimension(240,1) );
		this.separatorAfterProceedButton.setBackground( Color.BLACK );
		this.separatorAfterProceedButton.setForeground( Color.LIGHT_GRAY );
		this.leftPanel.add(this.separatorAfterProceedButton, "cell 1 8 3 1,growx");
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define a 'clear log' button in the left panel in the next section (after the first separator). <br>
	 * @since 1.0 <p>
	 */
		
	private void defineClearLogButton()
		{
		this.clearLogButton = new JButton( this.rcBundle.getString("clearLogButton") );
		this.clearLogButton.setEnabled( false );
		this.clearLogButton.setPreferredSize( new Dimension(135,23) );
		
		this.clearLogButton.addActionListener( new ActionListener() {
			public void actionPerformed( ActionEvent event ) {
				PrtStrApp.this.logTabTextArea.setText("Cleared. \u00B6" + System.lineSeparator().intern());
				}
			});
		
		this.leftPanel.add(this.clearLogButton, "cell 3 10,growx,aligny center");
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define a 'status' label used as an internal status bar of the left panel. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineStatusLabel()
		{
		this.statusLabel = new JLabel( this.rcBundle.getString("statusLabel") );
		this.statusLabel.setBorder( BorderFactory.createEtchedBorder(EtchedBorder.RAISED, null, null) );
		this.statusLabel.setEnabled( false );
		this.statusLabel.setFont( new Font("Consolas", Font.PLAIN, 12) );
		this.leftPanel.add(this.statusLabel, "cell 1 12,south");
		}
		
	//_________________________________________________________________________________________________________________________________________________________
	
	/**
	 * Create and define 'precautions' button in the left panel.<br>
	 * @since 1.0<p>
	 */
	
	private void definePrecautionsButton()
		{
		this.precautionsButton = new JButton( this.rcBundle.getString("precautionsButton") );
		
		this.precautionsButton.addActionListener( new ActionListener() {
			public void actionPerformed( ActionEvent event ) {
				String msg = "<html>Please be careful when you using the 'pages to miss' text area feature.<br><br>" + 
							 "Do not type ranges of pages that exceeded from the interval defined by<br>" + 
							 "the 'start' and 'end' page values.<br><br>" +
							 "For this exampled initial values...<br>" +
							 "Start page: 12<br>" +
							 "End page: 34<br><br>" +
							 "... do <u><b>not</b></u> try to type:<br>" +
							 "10-14,30-40,1-66<br><br>" + 
							 "<b>This kind of input data may lead to outputting the wrong results, depending<br>" + 
							 "on the place of the invalid range in the 'pages to miss' text area</b><br><br></html>"
							 .intern();
				JOptionPane.showMessageDialog(PrtStrApp.this.frame, msg, "Precautions", JOptionPane.INFORMATION_MESSAGE, null);
				}
			});
		
		this.leftPanel.add(this.precautionsButton, "cell 1 11");
		};
	
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define 'language' combo box in the left panel for GUI I18N feature.<br>
	 * @since 1.0<p>
	 */
		
	private void defineLanguageComboBox()
		{ 
		//this.languageComboBox = new JComboBox( comboBoxValues );
		//this.languageComboBox = new JComboBox<String>(); !!!
		this.languageComboBox = new JComboBox();
		
		this.languageComboBox.setModel( new DefaultComboBoxModel<String>( new String [] { 
				new Locale("en","US").getDisplayLanguage( this.locale ).toString(), 
				new Locale("pl","PL").getDisplayLanguage( this.locale ).toString()
				} ) );
		
		this.languageComboBox.addItemListener( new ItemListener() {
			public void itemStateChanged( ItemEvent event ) {
				if ( event.getStateChange() == ItemEvent.SELECTED ) {
					int selectedLanguage = PrtStrApp.this.languageComboBox.getSelectedIndex();
					
					switch ( selectedLanguage ) {
						case ( 0 ) : { // English
							PrtStrApp.this.locale = new Locale("en","US");
							PrtStrApp.this.revalidateComponentsTextsAfterLanguageCommuted( selectedLanguage );
							
							PrtStrApp.this.languageComboBox.setModel( new DefaultComboBoxModel<String>( new String [] {
									new Locale("en","US").getDisplayLanguage( PrtStrApp.this.locale ).toString(), 
									new Locale("pl","PL").getDisplayLanguage( PrtStrApp.this.locale ).toString()	
									} ) );
							}
							break;
						case ( 1 ) : { // Polish
							PrtStrApp.this.locale = new Locale("pl","PL");
							PrtStrApp.this.revalidateComponentsTextsAfterLanguageCommuted( selectedLanguage );
							
							// A problem with 'PrtStrApp.this.languageComboBox.setModel' here. 
							}
							break;
						}
					}
				}
			});
		
		
		this.languageComboBox.setSelectedIndex( 1 );
		this.leftPanel.add(this.languageComboBox, "cell 3 11,growx");
		};
		
	//_________________________________________________________________________________________________________________________________________________________

	/**
	 * Create and define the right panel of the main window. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineRightPanel()
		{
		// Defining the right panel itself.
		this.rightPanel = new JPanel();
		this.rightPanel.setPreferredSize( new Dimension(this.frame.getWidth(), 300) );
		this.rightPanel.setMinimumSize( new Dimension(420, 300) );
		this.rightPanel.setBorder( BorderFactory.createEtchedBorder(EtchedBorder.LOWERED, null, null) );
		this.frame.getContentPane().add(this.rightPanel, "cell 1 0,east");
		this.rightPanel.setLayout(new MigLayout("", "[grow]", "[grow]"));
		
		// Defining the tabbed pane of the right panel.
		this.tabbedPane = new JTabbedPane( JTabbedPane.TOP );
		
		this.tabbedPane.addMouseListener( new MouseAdapter() {
			@Override
			public void mousePressed( MouseEvent event ) 
				{
				final int selectedTab = PrtStrApp.this.tabbedPane.getSelectedIndex();
				
				switch ( selectedTab ) {
					case ( 0 ) : { // 'history log' tab
						PrtStrApp.this.clearLogButton.setEnabled( true );
						PrtStrApp.this.precautionsButton.setEnabled( false );
						}
						break;
					case ( 1 ) : { // 'output' tab
						PrtStrApp.this.precautionsButton.setEnabled( true );
						PrtStrApp.this.clearLogButton.setEnabled( false );
						}
						break;
					}
				}
			});
		
		this.rightPanel.add(this.tabbedPane, "cell 0 0,grow");
		
		// Defining following tabs (calling creators).
		this.defineLogTabComponents(); // {1}
		this.defineOutputTabComponents(); // {2}
		
		this.tabbedPane.setSelectedIndex( 1 ); // {N-1}
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define the components of 'Log' tab on the right panel. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineLogTabComponents()
		{
		// The first tab creation.
		JComponent logTab = new JPanel();
		this.tabbedPane.addTab(this.rcBundle.getString("historyLogTabName"), null, logTab, this.rcBundle.getString("historyLogTabPopup"));
		logTab.setLayout( new BorderLayout(0, 0) );
		
		// A scroll pane creation for having a viewport.
		this.logTabScrollPane = new JScrollPane();
		this.logTabScrollPane.setAutoscrolls( true );
		this.logTabScrollPane.setVerticalScrollBarPolicy( ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS );
		this.logTabScrollPane.setHorizontalScrollBarPolicy( ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED );
		logTab.add(this.logTabScrollPane, BorderLayout.CENTER);
		
		// A text area creation in viewport's context.
		this.logTabTextArea = new JTextArea();
		this.logTabTextArea.setWrapStyleWord( true );
		this.logTabTextArea.setEditable( false );
		this.logTabTextArea.setLineWrap( false );
		this.logTabTextArea.setFont( new Font("Consolas", Font.PLAIN, 12) );
		this.logTabTextArea.setText("Ready. \u00B6" + System.getProperty("line.separator").intern());
		this.logTabScrollPane.setViewportView( this.logTabTextArea );
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Create and define the components of 'Output' tab on the right panel. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineOutputTabComponents()
		{
		// The second tab creation.
		JComponent tab2 = new JPanel();
		this.tabbedPane.addTab(this.rcBundle.getString("outputTabName"), null, tab2, this.rcBundle.getString("outputTabPopup"));
		tab2.setLayout( new MigLayout("", "[grow]", "[][grow 130][][grow 130][][]") );
		
		// A label for 'pages to miss' scroll pane.
		this.outputTabPagesToMiss = new JLabel( this.rcBundle.getString("outputTabPagesToMissLabel") );
		tab2.add(this.outputTabPagesToMiss, "cell 0 0");
		
		// A label for 'output' scroll pane.
		this.outputTabOutputLabel = new JLabel( this.rcBundle.getString("outputTabOutputLabel") );
		tab2.add(this.outputTabOutputLabel, "cell 0 2");
		
		// A scroll pane for 'pages to miss' input data.
		this.pagesToMissScrollPane = new JScrollPane();
		this.pagesToMissScrollPane.setHorizontalScrollBarPolicy( ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER );
		tab2.add(this.pagesToMissScrollPane, "cell 0 1,grow");
		
		// A text area for 'pages to miss' input data.
		this.pagesToMissTextArea = new JTextArea();
		this.pagesToMissTextArea.setLineWrap( true );
		this.pagesToMissScrollPane.setViewportView( this.pagesToMissTextArea );
		
		// A scroll pane for 'output' data.
		this.outputScrollPane = new JScrollPane();
		this.outputScrollPane.setHorizontalScrollBarPolicy( ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER );
		tab2.add(this.outputScrollPane, "cell 0 3,grow");
		
		// A text area for 'output' data.
		this.outputTextArea = new JTextArea();
		this.outputTextArea.setCursor( Cursor.getPredefinedCursor( Cursor.TEXT_CURSOR ) );
		this.outputTextArea.setLineWrap( true );
		this.outputTextArea.setEditable( false );
		this.outputTextArea.setText( this.rcBundle.getString("outputTextAreaTextAtStart") );
		this.outputScrollPane.setViewportView( outputTextArea );
		
		// Calling creators.
		this.defineContextMenuForOutputTextArea();
		this.defineKeyListenerForPagesToMissTextArea();
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Provides a definition of KeyListener for 'pages to miss' text area on the right panel.<p>
	 * @since 1.0<p>
	 */
		
	private void defineKeyListenerForPagesToMissTextArea()
		{
		this.pagesToMissTextArea.addKeyListener( new KeyAdapter() {
			@Override
			public void keyPressed( KeyEvent keyEvent ) {
				// Enclosing scope Action class definition.
				Action action = new AbstractAction() {
					private static final long serialVersionUID = 1L;
	
					@Override
					public void actionPerformed( ActionEvent event ) {
						JOptionPane.showMessageDialog(PrtStrApp.this.frame, 
								"<html>Only <span style = \"text-decoration : underline\";>digits</span>, "
									+ "<span style = \"text-decoration : underline\";>comma</span> and "
									+ "<span style = \"text-decoration : underline\";>hyphen</span> will be treated as a valid input.<br><br>" +
								"<b>Please note that the additional inputted characters will not<br>" + 
								"be deleted from this text area automatically.</b><p><p></html>",
								"Improper input", JOptionPane.WARNING_MESSAGE, null);
						}
					};
					
				// Invoke action if regular keyboard character has been pressed.
				if ( Pattern.matches("[A-Za-z\t\n ~`!@#$%^&*()_=+{}\\|;:'\"<>./?\\[\\]]", String.valueOf( keyEvent.getKeyChar() )) == true ) {
					action.actionPerformed( null );
					}
					
				// Defining InputMap for key strokes.
				PrtStrApp.this.pagesToMissTextArea.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_F4, InputEvent.ALT_DOWN_MASK), "ALT+F4");
				PrtStrApp.this.pagesToMissTextArea.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_F1, 0), "F1");
				
				// Defining ActionMap for a key action.
				PrtStrApp.this.pagesToMissTextArea.getActionMap().put("ALT+F4", action);
				PrtStrApp.this.pagesToMissTextArea.getActionMap().put("F1", action);
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________

	/**
	 * Provides a definition of context menu (pop-up menu) for 'output' text area. <br>
	 * @since 1.0 <p>
	 */
		
	private void defineContextMenuForOutputTextArea()
		{
		this.outputTextArea.setComponentPopupMenu( new JPopupMenu() {
			private static final long serialVersionUID = -1L;
			private JMenuItem copyItem;
		
			// The instance initializer block used as a quasi-constructor.
				{
				this.addCopyEntry();
				}
				
			private void addCopyEntry() 
				{
				this.copyItem = new JMenuItem( PrtStrApp.this.rcBundle.getString("contextMenuForOutputTextArea->copyItem") );
				
				this.copyItem.addMouseListener( new MouseAdapter() {
					@Override
					public void mousePressed( MouseEvent event )  
						{
						if ( SwingUtilities.isLeftMouseButton( event ) ) 
							{
							String selectedText = PrtStrApp.this.outputTextArea.getSelectedText();
							
							// Copying the selected text to the system clipboard.
							StringSelection strSelect = new StringSelection( selectedText );
							Clipboard clpbrd = Toolkit.getDefaultToolkit().getSystemClipboard();
							
							try {
								clpbrd.setContents(strSelect, null);
								}
							catch ( IllegalStateException e ) {
								String msg = "The system clipboard is currently unavailable.".intern();
								System.err.println( msg );
								JOptionPane.showMessageDialog(PrtStrApp.this.frame, msg, "IllegalStateException", JOptionPane.INFORMATION_MESSAGE, null);
								}
							}
						}
					});
				
				this.add( this.copyItem );				
				}
			
			// Used via reflection.
			public void setNewLocalizedItemsTexts()
				{
				this.copyItem.setText( PrtStrApp.this.rcBundle.getString("contextMenuForOutputTextArea->copyItem") );
				}
			});
		}
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Checks whether start page value from start page text field is greater than end page value from end page text field. <br>
	 * @param _startPageValue If <b>true</b>, then this argument will be updated by a parsed value from start page text field. 
	 * @param _endPageValue If <b>true</b>, then this argument will be updated by a parsed value from end page text field. <p>
	 * @return <b>true</b> if test is passed, <b>false</b> if test is failed or an exception has been raised <p>
	 * @since 1.0 <p>
	 */
		
	private boolean checkStartAndEndPageTextFieldsValuesBeforeParsing( AtomicInteger _startPageValue, AtomicInteger _endPageValue )
		{
		String startPageField = this.startPageTextField.getText();
		String endPageField = this.endPageTextField.getText();
		int startPageValue = 0;
		int endPageValue = 0;
		
		try
			{
			startPageValue = Integer.parseInt( startPageField );
			endPageValue = Integer.parseInt( endPageField );
			
			if ( startPageValue > endPageValue )
				{
				String msg = "Start page value is greater than end page value. Operation canceled.";
				JOptionPane.showMessageDialog(this.frame, msg, "Improper start page value", JOptionPane.ERROR_MESSAGE, null);
				return ( false );
				}
			}
		catch ( NumberFormatException e )
			{
			String msg = "Start/end page is not an acceptable number. Operation canceled.";
			String className = Thread.currentThread().getStackTrace()[1].getClassName();
			String methodName = Thread.currentThread().getStackTrace()[1].getMethodName();
			String nl = System.lineSeparator();
			String errMsg = "NumberFormatException" + nl + className + "." + methodName + "()" + nl + nl + "Message: " + nl + e.getMessage() + nl;			
			JOptionPane.showMessageDialog(this.frame, msg + nl + nl + errMsg, "Invalid data", JOptionPane.ERROR_MESSAGE, null);
			return ( false );
			}
		
		_startPageValue.set( startPageValue );
		_endPageValue.set( endPageValue );
		
		return ( true );
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Parse 'pages to miss' text area content to find individual numbers and ranges of pages.
	 * It tries to parse integer numbers with help of two Scanner objects for comma (,) and hyphen (-) delimiters.
	 * If no exception has been raised than the values with be stored to external collections. <br>
	 * @param _individualPages A reference to a collection that will be used to add new elements of individual pages to miss data structure.
	 * @param _rangedPages A reference to a collection that will be used to add new elements of ranged pages to miss data structure.
	 * @param numberOfPagesCuttedOff A number of pages that has been founded and parsed.
	 * @param startPage A <em>startPage</em> value retrieved from the user.
	 * @param endPage An <em>endPage</em> value retrieved from the user.
	 * @since 1.0
	 */
		
	private void parsePagesToMissTextAreaContent( LinkedList<Integer> _individualPages, TreeMap<Integer,Integer> _rangedPages, AtomicInteger numberOfPagesCuttedOff,
												  int startPage, int endPage )
		{
		// Preparing for parsing.
		String content = this.pagesToMissTextArea.getText();
		Scanner commaScanner = new Scanner( content );
		Scanner hyphenScanner = null;
		String str = "";
		
		commaScanner.useDelimiter(",");
		
		// For each text of JTextArea content separated by a comma.
		while ( commaScanner.hasNext() )
			{
			str = commaScanner.next();
			
			// If scanned string has at least one hyphen then get two numbers.
			if ( Pattern.matches("^\\d*[-]+\\d*$", str) )
				{
				hyphenScanner = new Scanner( str );
				hyphenScanner.useDelimiter("-");
				String str1 = hyphenScanner.next();
				String str2 = hyphenScanner.next();
				int number1 = 0;
				int number2 = 0;
				
				try
					{
					// Dealing with ranged pages values.
					number1 = Integer.parseInt( str1 );
					number2 = Integer.parseInt( str2 );
					
					if ( number1 >= number2 )
						{
						hyphenScanner.close();
						throw ( new Exception("number1 >= number2") );
						}
					else
						{
						_rangedPages.put( number1, number2 );
						}
					
					for ( int i=number1; i<=number2; i++ ) {
						if ( (i <= endPage) && (i >= startPage) ) {
							numberOfPagesCuttedOff.set( numberOfPagesCuttedOff.get() + 1 );
							}
						}
					}
				catch ( NumberFormatException e )
					{
					String msg = "Invalid range of pages reached while checking 'pages to miss' content. Operation canceled.";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String nl = System.lineSeparator().intern();
					String errMsg = "NumberFormatException" + nl + className + "." + methodName + "()" + nl + nl + "Trying to parse: \'" + str + "\'" + nl;
					JOptionPane.showMessageDialog(this.frame, msg + nl + nl + errMsg, "Parsing problem", JOptionPane.ERROR_MESSAGE, null);
					break;
					}
				catch ( Exception e )
					{
					String msg = "Incorrect range of pages has been reached. Operation canceled.";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String nl = System.lineSeparator().intern();
					String errMsg = "Exception" + nl + className + "." + methodName + "()" + nl + nl + "Trying to parse: \'" + str + "\'" + nl;
					String intMsg = "Internal message: \'" + e.getMessage() + "\'" + nl;
					JOptionPane.showMessageDialog(this.frame, msg + nl + nl + errMsg + intMsg, "Range of pages problem", JOptionPane.ERROR_MESSAGE, null);
					break;
					}
				
				hyphenScanner.close();
				str = "";
				}
			// Otherwise get only one number.
			else
				{
				int number = 0;
				
				try
					{
					// Dealing with an individual page value.
					number = Integer.parseInt( str );
					_individualPages.add( number );
					}
				catch ( NumberFormatException e )
					{
					String msg = "Invalid character reached while checking 'pages to miss' content. Operation canceled.";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String nl = System.lineSeparator().intern();
					String errMsg = "NumberFormatException" + nl + className + "." + methodName + "()" + nl + nl + "Trying to parse: \'" + str + "\'" + nl;
					JOptionPane.showMessageDialog(this.frame, msg + nl + nl + errMsg, "Parsing problem", JOptionPane.ERROR_MESSAGE, null);
					break;
					}
				
				str = "";
				
				if ( (number <= endPage) && (number >= startPage) ) {
					numberOfPagesCuttedOff.set( numberOfPagesCuttedOff.get() + 1 );
					}
				}
			}
		
		commaScanner.close();
		};
		
	//_________________________________________________________________________________________________________________________________________________________
	
	/**
	 * Process the collections by sorting, deleting irrelevant data possibly stored in them, enrolling the range from start page to
	 * end page and removing pages to miss from the output data. The proper output data itself will be saved to the last formal parameter. <br>
	 * @param _individualPages This should be a list of individual pages to miss data to process further.
	 * @param _rangedPages This should be a sorted map of ranged pages to miss data to process further. 
	 * @param _startPage This should be a valid number of starting page. 
	 * @param _endPage This should be a valid number of ending page. 
	 * @param _outputPages This collection will be externally modified by the proper output. It should be empty at invoke. <p>
	 * @since 1.0 <p>
	 */
		
	private void processIndividualAndRangedPagesCollections( LinkedList<Integer> _individualPages, TreeMap<Integer,Integer> _rangedPages, 
															 final AtomicInteger _startPage, final AtomicInteger _endPage,
															 ArrayList<Integer> _outputPages)
		{
		// Sorting.
		Collections.sort( _individualPages );
		
		// Removing irrelevant data from individual pages to miss collection.
		Iterator<Integer> it = _individualPages.iterator();
		
		while ( it.hasNext() )
			{
			Integer value = it.next();
			
			if ( (value < _startPage.intValue()) || (value > _endPage.intValue()) )
				{
				it.remove();
				}
			}
		
		// Removing irrelevant data from ranged pages to miss collection.
		ArrayList<Integer> tmpList = new ArrayList<Integer>();
		
		for (Map.Entry<Integer,Integer> i : _rangedPages.entrySet())
			{
			Integer key = i.getKey();
			
			if ( (key < _startPage.intValue()) || (key > _endPage.intValue()) )
				{
				tmpList.add( key );
				}
			}
		
		it = tmpList.iterator();
		
		while ( it.hasNext() )
			{
			_rangedPages.remove( it.next() );
			}
		
		// Enrolling the numbers to 1-by-1 values as (startPage,startPage+1,...,endPage-1,endPage).
		LinkedList<Integer> enrolledPages = new LinkedList<Integer>();
		
		for (int i=_startPage.intValue(); i<=_endPage.intValue(); i++)
			{
			enrolledPages.add( i );
			}
		
		// Deleting individual pages to miss values from enrolled pages collection.
		it = _individualPages.iterator();
		
		while ( it.hasNext() )
			{
			int index = enrolledPages.indexOf( it.next() ); 
			
			if ( index != (-1) )
				{
				enrolledPages.remove( index );
				}
			}
		
		// Deleting ranged pages to miss values from enrolled pages collection.
		tmpList.removeAll( tmpList );
		
		for (Map.Entry<Integer,Integer> i : _rangedPages.entrySet())
			{
			Integer key = i.getKey();
			Integer value = i.getValue();
			
			for (int j=key; j<=value; j++)
				{
				tmpList.add( j );
				}
			}
		
		it = tmpList.iterator();
		
		while ( it.hasNext() )
			{
			int index = enrolledPages.indexOf( it.next() );
			
			if ( index != (-1) )
				{
				enrolledPages.remove( index );
				}
			}
		
		// Passing by the output data.
		it = enrolledPages.iterator();
		
		while ( it.hasNext() )
			{
			_outputPages.add( it.next() );
			}
		};
		
	//_________________________________________________________________________________________________________________________________________________________
	
	/**
	 * Group the output pages values according to the 'pages per sheet' selected item value to odd and even pairs and display
	 * this result data in the 'output' text area. <br>
	 * @param _outputPages A collection of proper output pages (with deleted pages to miss) and gained 1-by-1. <p>
	 * @return String array of two elements with odd and even pages string respectively. <p>
	 * @since 1.0 <p>
	 */
		
	private String[] groupByOddAndEvenPairs( final ArrayList<Integer> _outputPages )
		{
		StringBuilder oddPagesString = new StringBuilder();
		StringBuilder evenPagesString = new StringBuilder();
		
		switch ( this.pagesPerSheetComboBox.getSelectedItem().toString() )
			{
			case (  "1" ) : { this.executeUniversalOddEvenGroupingAlgorithm(_outputPages, (byte)(  1 ), oddPagesString, evenPagesString); } break;
			case (  "2" ) : { this.executeUniversalOddEvenGroupingAlgorithm(_outputPages, (byte)(  2 ), oddPagesString, evenPagesString); } break;
			case (  "4" ) : { this.executeUniversalOddEvenGroupingAlgorithm(_outputPages, (byte)(  4 ), oddPagesString, evenPagesString); } break;
			case (  "6" ) : { this.executeUniversalOddEvenGroupingAlgorithm(_outputPages, (byte)(  6 ), oddPagesString, evenPagesString); } break;
			case (  "9" ) : { this.executeUniversalOddEvenGroupingAlgorithm(_outputPages, (byte)(  9 ), oddPagesString, evenPagesString); } break;
			case ( "16" ) : { this.executeUniversalOddEvenGroupingAlgorithm(_outputPages, (byte)( 16 ), oddPagesString, evenPagesString); } break;
			}
		
		String ls = System.lineSeparator().intern();
		this.outputTextArea.setText("");
		this.outputTextArea.setText("odd: " + ls + oddPagesString + ls + ls + "even: " + ls + evenPagesString + ls);
		
		return ( new String[] { oddPagesString.toString(), evenPagesString.toString() } );
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * An universal to odd and even pairs grouping algorithm designed to work with different cases of 'pages per sheet' values. <br>
	 * @param _outputPages A collection of proper output pages (with deleted pages to miss) and gained 1-by-1.
	 * @param _groupOfNumbersNumber A parameter for optimizing the size of the internal array. Should be the same as 'pages per sheet' value,
	 * because it used also as a successor.
	 * @param _oddPagesString This string will be externally modified to just display it on the 'output' text area.
	 * @param _evenPagesString Same as <b>_oddPagesString</b>. String contains pages grouped in ranges of 'output' text area (if applicable). <p>
	 * @since 1.0 <p>
	 */
		
	private void executeUniversalOddEvenGroupingAlgorithm( final ArrayList<Integer> _outputPages, byte _groupOfNumbersNumber ,
														   StringBuilder _oddPagesString, StringBuilder _evenPagesString ) 
		{
		// Variables section.
		Iterator<Integer> it = _outputPages.iterator();
		boolean paritySwitchFlag = false;
		int i, j, k;
		final int SUCCESSOR = Math.abs( _groupOfNumbersNumber );
		Integer [] groupOfNumbers = new Integer [SUCCESSOR];
		Integer value;
		int ctr;
		
		// Traversing the ArrayList<Integer>.
		while ( it.hasNext() )
			{
			// Odd processing block.
			if ( paritySwitchFlag == false )
				{
				// Counter of gained numbers.
				ctr = 0;
				
				// Traversing the array for storing the numbers for further notice.
				for (i=0; i<SUCCESSOR; i++) 
					{
					groupOfNumbers[i] = 0;
					
					if ( it.hasNext() ) 
						{ 
						value = it.next();
						groupOfNumbers[i] = value;
						ctr++;
						} 
					}
				
				// Searching for the ranges of pages in gathered earlier group of numbers.
				for (j=0; j<ctr; j++) // 0..3
					{
					for (k=(ctr-1); k>=0; k--) // 3..0
						{
						if ( (j != k) && (groupOfNumbers[j] == (groupOfNumbers[k] - ((ctr-(ctr-k))-j) )) )
							{
							_oddPagesString.append(groupOfNumbers[j] + "-" + groupOfNumbers[k] + ",");
							j = k;
							break;
							}
						
						if ( j == k )
							{
							_oddPagesString.append(groupOfNumbers[j] + ",");
							}
						}
					}
				}
			// Even processing block.
			else
				{
				// Counter of gained numbers.
				ctr = 0;
				
				// Traversing the array for storing the numbers for further notice.
				for (i=0; i<SUCCESSOR; i++) 
					{
					groupOfNumbers[i] = 0;
					
					if ( it.hasNext() ) 
						{ 
						value = it.next();
						groupOfNumbers[i] = value;
						ctr++;
						} 
					}
				
				// Searching for the ranges of pages in gathered earlier group of numbers.
				for (j=0; j<ctr; j++) // 0..3
					{
					for (k=(ctr-1); k>=0; k--) // 3..0
						{
						if ( (j != k) && (groupOfNumbers[j] == (groupOfNumbers[k] - ((ctr-(ctr-k))-j) )) )
							{
							_evenPagesString.append(groupOfNumbers[j] + "-" + groupOfNumbers[k] + ",");
							j = k;
							break;
							}
						
						if ( j == k )
							{
							_evenPagesString.append(groupOfNumbers[j] + ",");
							}
						}
					}
				}
			
			// Switching the flag to opposite.
			paritySwitchFlag = !(paritySwitchFlag);
			}
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Revalidates language altering by re-caching ResourceBundle for corresponding locale .properties file.<p>
	 * @param _selectedLanguage An index of selected language on the combo box list.<p>
	 * @since 1.0<p>
	 */
		
	private void revalidateComponentsTextsAfterLanguageCommuted( int _selectedLanguage )
		{
		// Accessing new locale bundle file.
		ResourceBundle.clearCache();
		
		try {
			this.rcBundle = ResourceBundle.getBundle("PrtStrAppLocale", this.locale);
			}
		catch ( NullPointerException | MissingResourceException x ) {
			String msg = "An exception was thrown during an accessing for the ResourceBundle for changed Locale.<br><br>";
			String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
			String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
			String errMsg = "NullPointerException | MissingResourceException<br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
			String htmlMessage = "<html>" + msg + errMsg + "</html>";
			JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Accessing ResourceBundle problem", JOptionPane.ERROR_MESSAGE, null);
			}
		
		// Re-caching.
		if ( SwingUtilities.isEventDispatchThread() ) {
			// Calling a new Runnable because of problems in 'AWT-EventQueue-0' thread.
			SwingUtilities.invokeLater( new Runnable() {
				@Override
				public void run() {
					// Dealing with regular graphical interface components.
					PrtStrApp.this.clearLogButton.setText( PrtStrApp.this.rcBundle.getString("clearLogButton") );
					PrtStrApp.this.precautionsButton.setText( PrtStrApp.this.rcBundle.getString("precautionsButton") );
					PrtStrApp.this.endPageLabel.setText( PrtStrApp.this.rcBundle.getString("endPageLabel") );
					PrtStrApp.this.frame.setTitle( PrtStrApp.this.rcBundle.getString("frameName") );
					PrtStrApp.this.tabbedPane.setTitleAt(0, PrtStrApp.this.rcBundle.getString("historyLogTabName"));
					PrtStrApp.this.tabbedPane.setToolTipTextAt(0, PrtStrApp.this.rcBundle.getString("historyLogTabPopup"));
					PrtStrApp.this.tabbedPane.setTitleAt(1, PrtStrApp.this.rcBundle.getString("outputTabName"));
					PrtStrApp.this.tabbedPane.setToolTipTextAt(1, PrtStrApp.this.rcBundle.getString("outputTabPopup"));
					PrtStrApp.this.outputTabOutputLabel.setText( PrtStrApp.this.rcBundle.getString("outputTabOutputLabel") );
					PrtStrApp.this.outputTabPagesToMiss.setText( PrtStrApp.this.rcBundle.getString("outputTabPagesToMissLabel") );
					PrtStrApp.this.outputTextArea.setText( PrtStrApp.this.rcBundle.getString("outputTextAreaTextAtStart") );
					PrtStrApp.this.pagesPerSheetLabel.setText( PrtStrApp.this.rcBundle.getString("pagesPerSheetLabel") );
					PrtStrApp.this.precautionsButton.setText( PrtStrApp.this.rcBundle.getString("precautionsButton") );
					PrtStrApp.this.proceedButton.setText( PrtStrApp.this.rcBundle.getString("proceedButton") );
					PrtStrApp.this.startPageLabel.setText( PrtStrApp.this.rcBundle.getString("startPageLabel") );
					PrtStrApp.this.statusLabel.setText( PrtStrApp.this.rcBundle.getString("statusLabel") );
					
					// Dealing with 'output' text area context menu and with tray icon pop-up.
					JPopupMenu menu = PrtStrApp.this.outputTextArea.getComponentPopupMenu();
					PopupMenu trayMenu = PrtStrApp.this.trayIcon.getPopupMenu();
					
					try {
						Method method = menu.getClass().getMethod("setNewLocalizedItemsTexts");
						method.invoke( menu );
						Method trayMethod = trayMenu.getClass().getMethod("setNewLocalizedItemsTexts");
						trayMethod.invoke( trayMenu );
						}
					catch ( NoSuchMethodException | SecurityException x ) {
						String msg = "An exception was thrown during a re-caching the ResourceBundle for changed Locale.<br><br>";
						String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
						String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
						String errMsg = "NoSuchMethodException | SecurityException<br>" + className + "." + methodName + "()<br><br>" 
									  + "Internal message: " + x.getMessage();
						String htmlMessage = "<html>" + msg + errMsg + "</html>";
						JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Re-caching problem", JOptionPane.ERROR_MESSAGE, null);
						}
					catch ( InvocationTargetException | IllegalAccessException x ) {
						String msg = "An exception was thrown during a re-caching the ResourceBundle for changed Locale.<br><br>";
						String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
						String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
						String errMsg = "InvocationTargetException | IllegalAccessException<br>" + className + "." + methodName + "()<br><br>" 
									  + "Internal message: " + x.getMessage();
						String htmlMessage = "<html>" + msg + errMsg + "</html>";
						JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Re-caching problem", JOptionPane.ERROR_MESSAGE, null);
						}
					
					// Dealing with option dialogs regular buttons.
					UIManager.put("OptionPane.yesButtonText", PrtStrApp.this.rcBundle.getString("yesButtonText"));
					UIManager.put("OptionPane.noButtonText", PrtStrApp.this.rcBundle.getString("noButtonText"));
					UIManager.put("OptionPane.cancelButtonText", PrtStrApp.this.rcBundle.getString("cancelButtonText"));
					UIManager.put("OptionPane.titleButtonText", PrtStrApp.this.rcBundle.getString("titleButtonText"));
					
					// Dealing with the menu bar.
					PrtStrApp.this.programMenu.setText( PrtStrApp.this.rcBundle.getString("menuBar->Program") );
					PrtStrApp.this.getStackTraceMenuItem.setText( PrtStrApp.this.rcBundle.getString("menuBar->Program->getStackTraceMenuItem") );
					PrtStrApp.this.tryToRestartMenuItem.setText( PrtStrApp.this.rcBundle.getString("menuBar->Program->tryToRestartMenuItem") );
					PrtStrApp.this.exitMenuItem.setText( PrtStrApp.this.rcBundle.getString("menuBar->Program->exitMenuItem") );
					
					PrtStrApp.this.customizeMenu.setText( PrtStrApp.this.rcBundle.getString("menuBar->Customize") );
					PrtStrApp.this.propertiesOfUIManagerMenuItem.setText( PrtStrApp.this.rcBundle.getString("menuBar->Customize->propertiesOfUIManagerMenuItem") );
					
					PrtStrApp.this.aboutMenu.setText( PrtStrApp.this.rcBundle.getString("menuBar->About") );
					PrtStrApp.this.informationMenuItem.setText( PrtStrApp.this.rcBundle.getString("menuBar->About->informationMenuItem") );
					};
				});
			}
		else {
			String msg = "<html>The language has not been changed, because this application is not<br>" +
						 "running in the AWT EventQueue context.<br></html>".intern();
			String title = "Switching between languages".intern();
			JOptionPane.showMessageDialog(this.frame, msg, title, JOptionPane.WARNING_MESSAGE, null);
			}
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Provides a definition of WindowListener to the main JFrame. Used with program tray icon and its relative components.<p>
	 * @since 1.0<p>
	 */
		
	private void defineFrameListener()
		{
		try {
			// TrayIcon definition.
			this.trayIcon = new TrayIcon( new ImageIcon("src/images/trayicon.png").getImage() );
			trayIcon.setToolTip( this.rcBundle.getString("trayIconToolTip") + Thread.currentThread().getName() );
			
			// TrayIcon's PopupMenu definition.
			trayIcon.setPopupMenu( new PopupMenu() {
				private static final long serialVersionUID = 1L;
				private MenuItem restoreWindowItem = new MenuItem( PrtStrApp.this.rcBundle.getString("trayPopup->restoreWindowItem") );
				private MenuItem exitItem = new MenuItem( PrtStrApp.this.rcBundle.getString("trayPopup->exitItem") );
				
				// The instance initializer block used as a quasi-constructor.
					{
					this.add( this.restoreWindowItem );
					this.add( this.exitItem );
					this.addRestoreWindowItemListener();
					this.addExitItemListener();
					};
					
				private void addRestoreWindowItemListener() {
					this.restoreWindowItem.addActionListener( new ActionListener() {
						@Override
						public void actionPerformed( ActionEvent event ) {
							WindowListener[] listeners = PrtStrApp.this.frame.getWindowListeners();
							listeners[0].windowDeiconified( null );
							}
						});
					};
					
				private void addExitItemListener() {
					this.exitItem.addActionListener( new ActionListener() {
						@Override
						public void actionPerformed( ActionEvent event ) {
							PrtStrApp.this.frame.dispose();
							System.exit( 0 );
							};
						});
					};
				
				// Used via reflection.
				public void setNewLocalizedItemsTexts() {
					this.restoreWindowItem.setLabel( PrtStrApp.this.rcBundle.getString("trayPopup->restoreWindowItem") );
					this.exitItem.setLabel( PrtStrApp.this.rcBundle.getString("trayPopup->exitItem") );
					};
				});
			
			// TrayIcon's MouseListener related with its PopupMenu.
			trayIcon.addMouseListener( new MouseListener() {
				@Override
				public void mouseClicked( MouseEvent event ) {
					if ( (SwingUtilities.isLeftMouseButton(event)) /*|| ((event.getClickCount() == 2) && (!event.isConsumed()))*/ ) {
						event.consume();
						WindowListener[] listeners = PrtStrApp.this.frame.getWindowListeners();
						listeners[0].windowDeiconified( null );
						}
					};
				public void mouseEntered( MouseEvent event ) {
					};
				public void mouseExited( MouseEvent event ) {
					};
				public void mousePressed( MouseEvent event ) {
					};
				public void mouseReleased( MouseEvent event ) {
					};
				});
			
			// Main JFrame's WindowListener for using TrayIcon's feature.
			this.frame.addWindowListener( new WindowListener() {
				@Override
				public void windowActivated( WindowEvent event ) {
					javax.swing.UIManager.put("OptionPane.messageFont", new Font("System", Font.PLAIN, 12));
					};
				@Override
				public void windowClosed( WindowEvent event ) {
					};
				@Override
				public void windowClosing( WindowEvent event ) {
					String message = PrtStrApp.this.rcBundle.getString("windowClosingMessage").intern();
					String title = PrtStrApp.this.rcBundle.getString("windowClosingTitle").intern();
					int option = JOptionPane.showConfirmDialog(PrtStrApp.this.frame, message, title, JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null);
					if ( option == 0 ) { PrtStrApp.this.frame.dispose(); /* DO_NOTHING_ON_CLOSE */ }
					};
				@Override
				public void windowDeactivated( WindowEvent event ) {
					};
				@Override
				public void windowDeiconified( WindowEvent event ) {
					SystemTray.getSystemTray().remove( trayIcon );
					PrtStrApp.this.frame.setState( Frame.NORMAL );
					PrtStrApp.this.frame.setExtendedState( WindowEvent.WINDOW_DEICONIFIED );
					PrtStrApp.this.frame.setVisible( true );
					};
				@Override
				public void windowIconified( WindowEvent event ) {
					try {
						SystemTray.getSystemTray().add( trayIcon );
						trayIcon.displayMessage(PrtStrApp.this.rcBundle.getString("iconifiedMessage->Caption"),
											    PrtStrApp.this.rcBundle.getString("iconifiedMessage->Text"), TrayIcon.MessageType.INFO);
						PrtStrApp.this.frame.setState( Frame.ICONIFIED );
						PrtStrApp.this.frame.setExtendedState( WindowEvent.WINDOW_ICONIFIED );
						PrtStrApp.this.frame.setVisible( false );
						}
					catch ( AWTException x ) {
						String msg = "The desktop system tray is missing.<br><br>";
						String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
						String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
						String errMsg = "AWTException<br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
						String htmlMessage = "<html>" + msg + errMsg + "</html>";
						JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "SystemTray problem", JOptionPane.ERROR_MESSAGE, null);
						}
					};
				@Override
				public void windowOpened( WindowEvent event ) {
					};
				});
			}
		catch ( IllegalArgumentException x ) {
			String msg = "The <em>image</em> parameter of TrayIcon is null.<br><br>";
			String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
			String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
			String errMsg = "IllegalArgumentException<br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
			String htmlMessage = "<html>" + msg + errMsg + "</html>";
			JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "TrayIcon problem", JOptionPane.ERROR_MESSAGE, null);
			}
		catch ( HeadlessException x ) {
			String msg = "The  current environment does not support a keyboard, mouse or display.<br><br>";
			String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
			String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
			String errMsg = "HeadlessException<br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
			String htmlMessage = "<html>" + msg + errMsg + "</html>";
			JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "TrayIcon problem", JOptionPane.ERROR_MESSAGE, null);
			}
		catch ( UnsupportedOperationException x ) {
			String msg = "The system tray is not supported by the current platform.<br><br>";
			String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
			String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
			String errMsg = "UnsupportedOperationException<br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
			String htmlMessage = "<html>" + msg + errMsg + "</html>";
			JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "TrayIcon problem", JOptionPane.ERROR_MESSAGE, null);
			}
		catch ( SecurityException x ) {
			String msg = "The system tray permission has not been granted.<br>" + "The security manager indicates a security violation.<br><br>";
			String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
			String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
			String errMsg = "SecurityException<br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
			String htmlMessage = "<html>" + msg + errMsg + "</html>";
			JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "TrayIcon problem", JOptionPane.ERROR_MESSAGE, null);
			}
		};
		
	//_________________________________________________________________________________________________________________________________________________________

	/**
	 * Create and define a menu bar and its content for the main JFrame.<p>
	 * @since 1.0<p>
	 */
		
	private void defineMenuBar()
		{
		// Defining a menu bar itself.
		this.menuBar = new JMenuBar();
		this.frame.setJMenuBar( this.menuBar );
		
		// Defining a 'Program' menu branch.
		this.programMenu = new JMenu( this.rcBundle.getString("menuBar->Program") );
		this.getStackTraceMenuItem = new JMenuItem( this.rcBundle.getString("menuBar->Program->getStackTraceMenuItem") );
		JSeparator separator1 = new JSeparator();
		this.tryToRestartMenuItem = new JMenuItem( this.rcBundle.getString("menuBar->Program->tryToRestartMenuItem") );
		JSeparator separator2 = new JSeparator();
		this.exitMenuItem = new JMenuItem( this.rcBundle.getString("menuBar->Program->exitMenuItem") );
		
		this.defineMenuActionOfGetStackTrace();
		this.defineMenuActionOfTryToRestart();
		this.defineMenuActionOfExit();
		
		this.menuBar.add( this.programMenu );
		this.programMenu.add( this.getStackTraceMenuItem );
		this.programMenu.add( separator1 );
		this.programMenu.add( this.tryToRestartMenuItem );
		this.programMenu.add( separator2 );
		this.programMenu.add( this.exitMenuItem );
		
		// Defining a 'Customize' menu branch.
		this.customizeMenu = new JMenu( this.rcBundle.getString("menuBar->Customize") );
		this.propertiesOfUIManagerMenuItem = new JMenuItem( this.rcBundle.getString("menuBar->Customize->propertiesOfUIManagerMenuItem") );
		
		this.defineMenuActionOfUIManagerProperties();
		
		this.menuBar.add( this.customizeMenu );
		this.customizeMenu.add( this.propertiesOfUIManagerMenuItem );
		
		// Defining an 'About' menu branch.
		this.aboutMenu = new JMenu( this.rcBundle.getString("menuBar->About") );
		this.informationMenuItem = new JMenuItem( this.rcBundle.getString("menuBar->About->informationMenuItem") );
		
		this.defineMenuActionOfInformation();
		
		this.menuBar.add( this.aboutMenu );
		this.aboutMenu.add( this.informationMenuItem );
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Define an action for 'Exit' menu item of 'Program' branch of menu bar list.<p>
	 * @since 1.0<p>
	 */
		
	private void defineMenuActionOfExit()
		{
		this.exitMenuItem.addActionListener( new ActionListener() {
			@Override
			public void actionPerformed( ActionEvent evt ) {
				WindowListener [] listeners = PrtStrApp.this.frame.getWindowListeners();
				listeners[0].windowClosing( null );
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Define an action for 'Information' menu item of 'About' branch of menu bar list.<p>
	 * @since 1.0<p>
	 */
		
	private void defineMenuActionOfInformation()
		{
		this.informationMenuItem.addActionListener( new ActionListener() {
			@Override
			public void actionPerformed( ActionEvent evt ) {
				String msg = PrtStrApp.this.rcBundle.getString("informationMenuItemText");
				String title = "PrtStrApp".intern();
				JOptionPane.showMessageDialog(PrtStrApp.this.frame, msg, title, JOptionPane.PLAIN_MESSAGE, null);
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Define an action for 'Try to restart' menu item of 'Program' menu bar branch.<p>
	 * @since 1.0<p>
	 */
		
	private void defineMenuActionOfTryToRestart()
		{
		this.tryToRestartMenuItem.addActionListener( new ActionListener() {
			@Override
			public void actionPerformed( ActionEvent evt ) {
				try {
					final String javaBin = System.getProperty("java.home") + File.separator + "bin" + File.separator + "java";
					final File currentJar = new File( PrtStrApp.class.getProtectionDomain().getCodeSource().getLocation().toURI() );
					
					// Is it a .jar file check.
					if ( currentJar.getName().endsWith(".jar") == false ) {
						List<String> jvmArgs = ManagementFactory.getRuntimeMXBean().getInputArguments();
						ArrayList<String> commands = new ArrayList<String>(4 + jvmArgs.size() /* + args.length */);
						
						commands.add( javaBin );
						for ( String jvmArg : jvmArgs ) { commands.add( jvmArg ); }
						commands.add("-cp");
						commands.add( ManagementFactory.getRuntimeMXBean().getClassPath() );
						commands.add( PrtStrApp.class.getName() );
						//for ( String arg : args ) { commands.add( arg ); }
						
						String[] commandArray = new String[commands.size()];
						commandArray = commands.toArray( commandArray );
						
						// Null means the same environment and the same working directory.
						Process process = Runtime.getRuntime().exec( commandArray, null, null );
						Thread.sleep( 250L );
						
						if ( (process.isAlive() == false) || (process == null) ) {
							throw ( new IllegalArgumentException("Cannot find location of the .jar file.") );
							}
						else {
							Runtime.getRuntime().exit( 0 );
							}
						}
					else {
						// Building a command: java -jar app.jar
						final ArrayList<String> command = new ArrayList<String>();
						command.add( javaBin );
						command.add("-jar");
						command.add( currentJar.getPath() );
						
						final ProcessBuilder builder = new ProcessBuilder( command );
						builder.start();
						Thread.sleep( 250L );
						System.exit( 0 );
						}
					}
				catch ( IOException x ) {
					String msg = "An I/O error has occured.<br><br>";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String errMsg = "<b>IOException</b><br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
					String htmlMessage = "<html>" + msg + errMsg + "</html>";
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Restarting problem", JOptionPane.ERROR_MESSAGE, null);
					}
				catch ( SecurityException x ) {
					String msg = "The security manager does not permit an access to the resource.<br><br>";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String errMsg = "<b>SecurityException</b><br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
					String htmlMessage = "<html>" + msg + errMsg + "</html>";
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Restarting problem", JOptionPane.ERROR_MESSAGE, null);
					}
				catch ( InterruptedException x ) {
					String msg = "One of the thread has interrupted the current thread. Status of the current thread has been cleared.<br><br>";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String errMsg = "<b>InterruptedException</b><br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
					String htmlMessage = "<html>" + msg + errMsg + "</html>";
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Restarting problem", JOptionPane.ERROR_MESSAGE, null);
					}
				catch ( NullPointerException x ) {
					String msg = "At least one of the parameter is a null value.<br><br>";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String errMsg = "<b>NullPointerException</b><br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
					String htmlMessage = "<html>" + msg + errMsg + "</html>";
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Restarting problem", JOptionPane.ERROR_MESSAGE, null);
					}
				catch ( IndexOutOfBoundsException x ) {
					String msg = "The command is an empty list.<br><br>";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String errMsg = "<b>IndexOutOfBoundsException</b><br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
					String htmlMessage = "<html>" + msg + errMsg + "</html>";
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Restarting problem", JOptionPane.ERROR_MESSAGE, null);
					}
				catch ( IllegalArgumentException x ) {
					String msg = "The preconditions on one of the parameter do not hold.<br><br>";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String errMsg = "<b>IllegalArgumentException</b><br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
					String htmlMessage = "<html>" + msg + errMsg + "</html>";
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Restarting problem", JOptionPane.ERROR_MESSAGE, null);
					}
				catch ( URISyntaxException x ) {
					String msg = "URL is not formatted strictly according to RFC2396, thus cannot be converted.<br><br>";
					String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
					String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
					String errMsg = "<b>URISyntaxException</b><br>" + className + "." + methodName + "()<br><br>" + "Internal message: " + x.getMessage();
					String htmlMessage = "<html>" + msg + errMsg + "</html>";
					JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Restarting problem", JOptionPane.ERROR_MESSAGE, null);
					}
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Define an action for 'Get stack trace' menu item of 'Program' menu bar branch.<p>
	 * @since 1.0<p>
	 */
		
	private void defineMenuActionOfGetStackTrace()
		{
		this.getStackTraceMenuItem.addActionListener( new ActionListener() {
			@Override
			public void actionPerformed( ActionEvent evt ) {
				String msg = "A stack trace of the current thread.<br><br>";
				String className = Thread.currentThread().getStackTrace()[1].getClassName().intern();
				String fileName = Thread.currentThread().getStackTrace()[1].getFileName().intern();
				String methodName = Thread.currentThread().getStackTrace()[1].getMethodName().intern();
				int lineNumber = Thread.currentThread().getStackTrace()[1].getLineNumber();
				boolean isNativeMethod = Thread.currentThread().getStackTrace()[1].isNativeMethod();
				String stackTraceElements = Thread.currentThread().getStackTrace()[1].toString();
				String errMsg = "<b>Class name:</b> " + className + "<br>" + 
								"<b>File name:</b> " + fileName + "<br>" +
								"<b>Method name:</b> " + methodName + "<br>" +
								"<b>Line number:</b> " + lineNumber + "<br>" +
								"<b>Native method:</b> " + isNativeMethod + "<br><br>" +
								"<b>Stack trace elements:</b><br>" + stackTraceElements + "<br><br>";
				String htmlMessage = "<html>" + msg + errMsg + "</html>";
				JOptionPane.showMessageDialog(PrtStrApp.this.frame, htmlMessage, "Menu item feature", JOptionPane.INFORMATION_MESSAGE, null);
				}
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Define an action for 'Properties of UIManager' menu item of 'Customize' menu bar branch.<p>
	 * @since 1.0<p>
	 */
		
	private void defineMenuActionOfUIManagerProperties()
		{
		this.propertiesOfUIManagerMenuItem.addActionListener( new ActionListener() {
			@Override
			public void actionPerformed( ActionEvent evt ) {
				// Defining the dialog window of the main frame.
				JDialog dialog = new JDialog(PrtStrApp.this.frame, "UIManager");
				dialog.setResizable( false );
				dialog.setModalityType( Dialog.ModalityType.APPLICATION_MODAL );
				dialog.setSize( new Dimension(520,220) );
				dialog.setPreferredSize( new Dimension(520,220) );
				dialog.setDefaultCloseOperation( JDialog.DISPOSE_ON_CLOSE );
				
				// Creating the dialog.
				JPanel comboBoxPane = new JPanel();
				String [] comboBoxItems = { "{none}","OptionPane.messageFont" };
				JComboBox<String> comboBox = new JComboBox<String>( comboBoxItems );
				comboBox.setEditable( false );
				comboBoxPane.add( comboBox );
				
				JPanel cardOfNone = new JPanel();
				cardOfNone.add( new JLabel("Choose an option from the list.") );
				
				JPanel cardOfOptionPaneMessageFont = new JPanel();
				cardOfOptionPaneMessageFont.add( new JLabel("Font: ") );
				java.awt.GraphicsEnvironment ge = java.awt.GraphicsEnvironment.getLocalGraphicsEnvironment();
				Font [] fonts = ge.getAllFonts();
				String [] availableFonts = new String [fonts.length];
				for (int i=0; i<fonts.length; i++) { availableFonts[i] = fonts[i].getFamily(PrtStrApp.this.locale); };
				TreeMap<Integer,String> fontsList = new TreeMap<Integer,String>();
				for (int i=0; i<availableFonts.length; i++) { if ( fontsList.containsValue(availableFonts[i]) == false ) { fontsList.put(i,availableFonts[i]); } };
				//for (Map.Entry<Integer,String> i : fontsList.entrySet()) { System.out.println( i.getKey() + " " + i.getValue() ); };
				String [] fontsTable = new String [fontsList.size()];
				Object [] values = fontsList.values().toArray();
				for (int i=0; i<fontsList.size(); i++) { fontsTable[i] = values[i].toString(); };
				JComboBox<String> cbFonts = new JComboBox<String>( fontsTable );
				cbFonts.setMaximumRowCount( 11 );
				cardOfOptionPaneMessageFont.add( cbFonts );
				cardOfOptionPaneMessageFont.add( new JLabel("Style: ") );
				String [] styleItems = new String [] { "Plain","Bold","Italic" };
				JComboBox<String> cbStyle = new JComboBox<String>( styleItems );
				cardOfOptionPaneMessageFont.add( cbStyle );
				cardOfOptionPaneMessageFont.add( new JLabel("Size: ") );
				JSpinner spinner = new JSpinner( new SpinnerNumberModel(11,6,44,1) );
				cardOfOptionPaneMessageFont.add( spinner );
				JPanel okButtonPanel = new JPanel( new BorderLayout() );
				JLabel text = new JLabel("<html><br>Lorem ipsum<br></html>");
				JButton okButton = new JButton("OK");
				okButtonPanel.add(text, BorderLayout.CENTER);
				okButtonPanel.add(okButton, BorderLayout.SOUTH);
				cardOfOptionPaneMessageFont.add( okButtonPanel );
				
				JPanel cardsPanel = new JPanel( new CardLayout() );
				cardsPanel.add(cardOfNone,comboBoxItems[0]);
				cardsPanel.add(cardOfOptionPaneMessageFont,comboBoxItems[1]);
				
				dialog.getContentPane().add(comboBoxPane, BorderLayout.PAGE_START);
				dialog.getContentPane().add(cardsPanel, BorderLayout.CENTER);
				
				comboBox.addItemListener( new ItemListener() {
					@Override
					public void itemStateChanged( ItemEvent evt ) {
						CardLayout cl = (CardLayout)(cardsPanel.getLayout());
						cl.show(cardsPanel, (String)(evt.getItem()));
						};
					});
				
				okButton.addActionListener( new ActionListener() {
					@Override
					public void actionPerformed( ActionEvent evt ) {
						String selectedFont = cbFonts.getItemAt( cbFonts.getSelectedIndex() );
						int selectedStyle = 0;
						int selectedSize = Integer.parseInt( spinner.getModel().getValue().toString() );
						
						switch ( cbStyle.getSelectedIndex() ) {
							case ( 0 ) : { selectedStyle = Font.PLAIN; } break;
							case ( 1 ) : { selectedStyle = Font.BOLD; } break;
							case ( 2 ) : { selectedStyle = Font.ITALIC; } break;
							}
						
						Font newFont = new Font(selectedFont, selectedStyle, selectedSize);
						javax.swing.UIManager.put("OptionPane.messageFont", newFont);
						PrtStrApp.this.outputTextArea.setFont( newFont );
						PrtStrApp.this.outputTextArea.revalidate();
						PrtStrApp.this.outputTextArea.repaint();
						
						String title = "UIManager.put".intern();
						String message = "The JOptionPane's message font has been changed.".intern();
						JOptionPane.showMessageDialog(dialog, message, title, JOptionPane.INFORMATION_MESSAGE, null);
						};	
					});
				
				// Finishing the stub
				dialog.pack();
				dialog.setLocationRelativeTo( null );
				dialog.setVisible( true );
				};
			});
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	/**
	 * Counts a load factor (fulfillment) of pages considered in the processing (range between <em>startPage</em> and <em>endPage</em> minus <em>pagesToMiss</em>)
	 * and all of the range (range between <em>startPage</em> and <em>endPage</em> only).
	 * @param numberOfPagesCuttedOff The number of pages that was missed during processing.
	 * @return The number of real pages to print.
	 * @since 1.0
	 */
		
	private double countLoadFactor( int numberOfPagesCuttedOff )
		{
		int startPage = Integer.parseInt( startPageTextField.getText().intern() );
		int endPage = Integer.parseInt( endPageTextField.getText().intern() );
		int rangeOfPages = endPage - startPage;
		int pagesConsidered = rangeOfPages - numberOfPagesCuttedOff + 1;
		int pagesPerSheetSelected = Integer.parseInt( this.pagesPerSheetComboBox.getSelectedItem().toString() );
		double loadFactor = (double)(pagesConsidered) / (double)(pagesPerSheetSelected);
		
		return ( loadFactor );
		};
		
	//_________________________________________________________________________________________________________________________________________________________
		
	};

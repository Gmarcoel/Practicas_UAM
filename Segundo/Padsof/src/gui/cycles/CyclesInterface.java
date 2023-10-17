package gui.cycles;

import java.awt.*;

import java.awt.event.*;
import java.util.ArrayList;

import javax.swing.*;
import app.*;
import users.*;
import performances.*;
import events.*;
import events.CyclePass;
import gui.mainform.MainFrame;

/**
 * This is a class that allow us to create the cylces interface
 * 
 * @author Daniel Varela Sanchez daniel.varelas@estudiante.uam.es
 * @author Javier Lopez de la Nieta Lujan
 *         javier.lopezdelanieta@estudiante.uam.es
 * @author Guillermo Martin-Coello Juarez
 *         guillermo.martin-coello@estudiante.uam.es
 */
public class CyclesInterface extends JPanel{
	/**
	 * Class constructor
	 * @param parent Mainframe
	 * @param app Theater app
	 */
	public CyclesInterface (MainFrame parent, TheaterApp app){
                JPanel list = new JPanel();
		
		list.setLayout(new GridLayout(0,2));
                Customer c = (Customer)app.getCustomer(parent.getCurrentUser());
                ArrayList<Pass> eliminate = new ArrayList<>();
                for(Pass p : c.getPasses()){
                	if(p instanceof CyclePass) {
                		if(((CyclePass)p).getCanGoToList().size()==0) {
                			eliminate.add(p);
                		}
                	}
                }
                for(Pass p : eliminate) {
                	c.removePass(p);
                }
                if(c.getAnnualPass()!=null) {
                	if(((AnnualPass)c.getAnnualPass()).checkIfValidAnnualPass()==false) {
                		c.removePass(c.getAnnualPass());
                	}
                }
                for(Pass p : c.getPasses()){
					list.add(new CycleButton(app, parent, p, c));
                }														// no esta esto en events interface? osea los cycle "son" events 
                this.add(list);											// o esto son passes
                														// la vida es una lenteja

		JScrollPane scroll = createScrollBar(list);
		this.add(scroll);
        
	}
	
	/**
	 * creates a scroll bar
	 * @param son panel to be inserted in the scrollbar
	 * @return a scrollpane 
	*/
	public static JScrollPane createScrollBar(JPanel son) {
	    JScrollPane scrollPane = new JScrollPane(son);
	    scrollPane.setPreferredSize(new Dimension(1500, 700));
	    return scrollPane;
	    
	}
	
}

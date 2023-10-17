/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * VisaCancelacionJMSBean.java
 */

package ssii2.visa;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ejb.EJBException;
import javax.ejb.MessageDriven;
import javax.ejb.MessageDrivenContext;
import javax.ejb.ActivationConfigProperty;
import javax.jms.MessageListener;
import javax.jms.Message;
import javax.jms.TextMessage;
import javax.jms.JMSException;
import javax.annotation.Resource;
import java.util.logging.Logger;
import java.util.*;
import java.sql.Statement;


/**
 * @author jaime
 */
@MessageDriven(mappedName = "jms/VisaPagosQueue")
public class VisaCancelacionJMSBean extends DBTester implements MessageListener {
    static final Logger logger = Logger.getLogger("VisaCancelacionJMSBean");
    @Resource
    private MessageDrivenContext mdc;

    private static final String UPDATE_CANCELA_QRY = "update pago set codRespuesta=999 where idautorizacion=?";
    // TODO : Definir UPDATE sobre la tabla pagos para poner
    // codRespuesta a 999 dado un código de autorización

    private static final String RECT_SALDO = "update tarjeta set saldo=saldo+" +
            "(select importe from pago where idautorizacion=?)" +
            "where numerotarjeta=" +
            "(select numerotarjeta from pago where idautorizacion=?)";
    /*
     * Consulta SQL necesaria para obtener el código de respuesta del pago cuyo
     * idAutorizacion
     * coincida con lo recibido por el mensaje
     */
    private static final String SELECT_CODIGO_RESPUESTA = "select codRespuesta from pago"
            + " where idAutorizacion=?";


    public VisaCancelacionJMSBean() {
    }

    // TODO : Método onMessage de ejemplo
    // Modificarlo para ejecutar el UPDATE definido más arriba,
    // asignando el idAutorizacion a lo recibido por el mensaje
    // Para ello conecte a la BD, prepareStatement() y ejecute correctamente
    // la actualización

    public void onMessage(Message inMessage) {
        TextMessage msg = null;
        Connection con = null;
        Statement stmt = null;
        ResultSet rs = null;
        boolean ret = false;
        String qry = null;
        PreparedStatement pstmt = null;


        try {
            if (inMessage instanceof TextMessage) {
                msg = (TextMessage) inMessage;
                logger.info("MESSAGE BEAN: Message received: " + msg.getText());

                int idAutorizacion = Integer.parseInt(msg.getText());
                String x = Integer.toString(idAutorizacion);
                con = getConnection();



                    
                String insert  = SELECT_CODIGO_RESPUESTA;
                //errorLog(insert);
                pstmt = con.prepareStatement(insert);
                pstmt.setString(1, x);
                ret = false;
                rs = stmt.executeQuery(insert);

                
                if (rs.getString("codRespuesta").contains("000")){
                    String insert2 = UPDATE_CANCELA_QRY;
                    //errorLog(insert2);
                    pstmt = con.prepareStatement(insert2);
                    pstmt.setString(1, x);
                    ret = false;
                    if (!stmt.execute(insert2)
                    && stmt.getUpdateCount() == 1) {
                        ret = true;
			        }

                    if(ret == true){
                        String insert3 = RECT_SALDO;
                        //errorLog(insert3);
                        pstmt = con.prepareStatement(insert3);
                        pstmt.setString(1,x);
                        pstmt.setString(2,x);
                        ret = false;
                        if (!stmt.execute(insert3)
                        && stmt.getUpdateCount() == 1) {
                            ret = true;
                        }
                    }
                }   

            } else {
                logger.warning(
                        "Message of wrong type: "
                                + inMessage.getClass().getName());
            }
        } catch (JMSException e) {
            e.printStackTrace();
            mdc.setRollbackOnly();
        } catch (Throwable te) {
            te.printStackTrace();
        } finally {
            try {
                if (rs != null) {
                    rs.close(); rs = null;
                }
                if (stmt != null) {
                    stmt.close(); stmt = null;
                }
                if (pstmt != null) {
                    pstmt.close(); pstmt = null;
                }
                if (con != null) {
                    closeConnection(con); con = null;
                }
            } catch (SQLException e) {
            }
        }
    }

}

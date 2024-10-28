import { createStackNavigator } from '@react-navigation/stack'
import Historicos from './Historicos'
import Historico from './Historico'

const HistoricoNav = createStackNavigator()

const HistoricoNavScreen = ({historico}) => (
   <HistoricoNav.Navigator >
     <HistoricoNav.Screen name="Lista de Transações">
       { props => <Historicos {...props} historico={historico}/> }
     </HistoricoNav.Screen>
     <HistoricoNav.Screen name="Historico" options={({ route }) => ({ title: route.params.historico.historico })}>
       { props => <Historico {...props} /> }
     </HistoricoNav.Screen>
   </HistoricoNav.Navigator>
 )
export default HistoricoNavScreen


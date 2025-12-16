if ( ( port_mode_numeric_p->pm1 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm1 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc1 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc1 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc1 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc1 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
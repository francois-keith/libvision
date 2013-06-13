

    coshell->ExecuteACommand("loadPlugin rotation-steering.so");
    coshell->ExecuteACommand("new RotationSteering rsteering");

//ligne necessaire au fonctionnement pas sur pour periodc call
                m_coshell->ExecuteACommand("plug dyn.ffposition rsteering.positionIN");
                m_coshell->ExecuteACommand("OpenHRP.periodicCall addSignal rsteering.positionOUT");
                m_coshell->ExecuteACommand("plug rsteering.positionOUT pg.velocitydes");

                std::stringstream setRotationAngleString;
                setRotationAngleString<<"rsteering.setRotationAngle "<<headPosePan;

                m_coshell->ExecuteACommand(setRotationAngleString.str());
                m_coshell->ExecuteACommand("rsteering.rotate");

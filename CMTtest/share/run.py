#!/usr/bin/env python
# usage: ___example___

import Sniper

def get_parser():

    import argparse

    parser = argparse.ArgumentParser(description='muon waveform reconstruction')

    import argparse

    parser = argparse.ArgumentParser(description='muon waveform reconstruction.')
    parser.add_argument("--evtmax", type=int, default=-1, help="events to be processed")
    parser.add_argument("--input", default="evt-55_5_170_0_SPMT_elecsim_enableFadc.root", help="input file name")
    parser.add_argument("--output", default="vt-55_5_170_0_SPMT_calib_enableFadc.root", help="output file name")
    parser.add_argument("--loglevel", default="Info", choices=["Test", "Debug", "Info", "Warn", "Error", "Fatal"],)
    parser.add_argument("--threshold", default="0.1", type=float, help="threshold for muon first hit time")
    parser.add_argument("--length", default="1250", type=int, help="readout window length in ns")
    parser.add_argument("--user-output", default="user_output.root", help="user output file name")

    return parser

DATA_LOG_MAP = {"Test":0, "Debug":2, "Info":3, "Warn":4, "Error":5, "Fatal":6}

if __name__ == "__main__":

    parser = get_parser()
    args = parser.parse_args()

    task = Sniper.Task("task")
    task.asTop()
    task.setEvtMax(args.evtmax)
    task.setLogLevel(DATA_LOG_MAP[args.loglevel])

    # Create Data Buffer Svc
    import DataRegistritionSvc
    task.createSvc("DataRegistritionSvc")

    # Create Buffer Svc
    import BufferMemMgr
    bufMgr = task.createSvc("BufferMemMgr")
    bufMgr.property("TimeWindow").set([0, 0])

    # Create IO Svc
    import RootIOSvc
    inputsvc = task.createSvc("RootInputSvc/InputSvc")
    inputsvc.property("InputFile").set([args.input])

    roSvc = task.createSvc("RootOutputSvc/OoutputSvc")
    roSvc.property("OutputStreams").set({"/Event/CalibEvent":args.output})

    # User Output
    import RootWriter
    rootwriter = task.createSvc("RootWriter")
    rootwriter.property("Output").set({"CALIBEVT":args.user_output})

    # Import MuonWaveRec
    Sniper.loadDll("libMuonWaveRec.so")
    muonWaveRec = task.createAlg("MuonWaveRec")
    muonWaveRec.property("Threshold").set(args.threshold)
    muonWaveRec.property("Length").set(args.length)
    task.show()
    task.run()
    

import pymel.core as pm
import logging

log = logging.getLogger("ui")

class BaseTemplate(pm.ui.AETemplate):
    
    def addControl(self, control, label=None, **kwargs):
        pm.ui.AETemplate.addControl(self, control, label=label, **kwargs)
        
    def beginLayout(self, name, collapse=True):
        pm.ui.AETemplate.beginLayout(self, name, collapse=collapse)
        

class AECoronaWireTemplate(BaseTemplate):
    def __init__(self, nodeName):
        BaseTemplate.__init__(self,nodeName)
        log.debug("AECoronaLightTemplate")
        self.thisNode = None
        self.node = pm.PyNode(self.nodeName)
        pm.mel.AEswatchDisplay(nodeName)
        self.beginScrollLayout()
        self.buildBody(nodeName)
        allAttributes = self.node.listAttr()
        allowedAttributes = ["useWorldSpace", "showVertices", "allEdges", "edgeWidth", "vertexWidth", "showEdges"]
        for att in allAttributes:
            att = att.split(".")[-1]
            if not att in allowedAttributes:
                self.suppress(att)
        self.addExtraControls("ExtraControls")
        self.endScrollLayout()
        
    def buildBody(self, nodeName):
        self.thisNode = pm.PyNode(nodeName)
        self.beginLayout("Wire Settings" ,collapse=0)
        self.beginNoOptimize()
        self.addControl("useWorldSpace", label="Color")
        self.addControl("showVertices", label="Multiplier")
        self.addControl("showEdges", label="Opacity")
        self.addControl("allEdges", label="Emit Light")
        self.addControl("edgeWidth", label="Directionality")
        self.addControl("vertexWidth", label="Double Sided")
        self.endNoOptimize()
        self.endLayout()
                
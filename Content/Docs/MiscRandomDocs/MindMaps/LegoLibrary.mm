<map version="0.8.0 RC2">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node ID="Freemind_Link_1527000853" LINK="FreedomEngine.mm" TEXT="Lego Library">
<node COLOR="#338800" ID="Freemind_Link_1646487551" POSITION="right" TEXT="Vector2D&#xa;2 part representation of a position or displacement">
<node COLOR="#ff0000" ID="Freemind_Link_1720250426" TEXT="Real x"/>
<node COLOR="#ff0000" ID="Freemind_Link_479627597" TEXT="Real y"/>
<node ID="Freemind_Link_192609851" TEXT="Methods">
<node ID="Freemind_Link_660902897" TEXT="Vector Generic">
<node COLOR="#990000" ID="Freemind_Link_308426932" TEXT="Normalize( )&#xa;Normalizes the Vector (Makes length = 1)"/>
<node COLOR="#990000" ID="Freemind_Link_306518512" TEXT="NormalizeRet( )&#xa;Normalizes the Vector, and returns the magnitude (length)"/>
<node COLOR="#990000" ID="Freemind_Link_1992503516" TEXT="Normal( )&#xa;Returns the normal of the vector, and does not normalize"/>
<node COLOR="#990000" ID="Freemind_Link_1024413165" TEXT="Magnitude( )&#xa;Returns the length of the vector">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_826767984" TEXT="MagnitudeSquared( )&#xa;Returns the squared length of the vector">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_1360037621" TEXT="Manhattan( )&#xa;Returns the manhattan length of the vector">
<edge WIDTH="thin"/>
</node>
</node>
<node ID="Freemind_Link_917459810" TEXT="Conversion">
<node COLOR="#990000" ID="Freemind_Link_188745394" TEXT="ToScalarVector( )">
<arrowlink DESTINATION="Freemind_Link_100151073" ENDARROW="Default" ENDINCLINATION="235;0;" ID="Freemind_Arrow_Link_1768893802" STARTARROW="None" STARTINCLINATION="235;0;"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_494413071" TEXT="ToMatrix2x1( )">
<arrowlink DESTINATION="Freemind_Link_1738034803" ENDARROW="Default" ENDINCLINATION="282;0;" ID="Freemind_Arrow_Link_1863850160" STARTARROW="None" STARTINCLINATION="282;0;"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_65141390" TEXT="ToMatrix1x2( )">
<arrowlink DESTINATION="Freemind_Link_1271250104" ENDARROW="Default" ENDINCLINATION="295;0;" ID="Freemind_Arrow_Link_1678601226" STARTARROW="None" STARTINCLINATION="295;0;"/>
</node>
</node>
<node COLOR="#990000" ID="Freemind_Link_553073598" TEXT="Tangent( )&#xa;Returns a perpendicular vector."/>
</node>
<node ID="Freemind_Link_1243274815" TEXT="Constants">
<node COLOR="#006699" ID="Freemind_Link_1499525244" TEXT="Vector2D Zero&#xa;A Vector with all elements of zero">
<edge WIDTH="thin"/>
<font NAME="SansSerif" SIZE="12"/>
</node>
<node COLOR="#006699" ID="Freemind_Link_749988414" TEXT="Vector2D Identity&#xa;A vector when scaled by returns the same vector">
<edge WIDTH="thin"/>
<font NAME="SansSerif" SIZE="12"/>
</node>
</node>
<node ID="Freemind_Link_743626639" TEXT="Derivatives">
<node COLOR="#338800" ID="Freemind_Link_100151073" TEXT="ScalarVector2D&#xa;Temporary type for reinterpretations of the vector as a multi part scalar">
<edge WIDTH="thin"/>
<font NAME="SansSerif" SIZE="12"/>
</node>
<node COLOR="#338800" ID="Freemind_Link_1738034803" TEXT="Matrix2x1&#xa;Temporary type for reinterpretations of the vector for Matrix operations"/>
<node COLOR="#338800" ID="Freemind_Link_1271250104" TEXT="Matrix1x2&#xa;Temporary type for reinterpretations of the vector for Matrix operations"/>
</node>
</node>
<node COLOR="#338800" ID="Freemind_Link_1817793578" POSITION="left" TEXT="Matrix2x2&#xa;2x2 basis and accumulation structure"/>
<node COLOR="#338800" ID="Freemind_Link_689217785" POSITION="left" TEXT="Real&#xa;Wrapper for desired floating point type">
<node COLOR="#ff0000" ID="Freemind_Link_385541167" TEXT="float Data"/>
<node ID="Freemind_Link_122259780" TEXT="Methods">
<edge WIDTH="thin"/>
<font NAME="SansSerif" SIZE="12"/>
<node ID="Freemind_Link_816554494" TEXT="Vector Generic">
<edge WIDTH="thin"/>
<node COLOR="#990000" ID="Freemind_Link_246434067" TEXT="Normalize( )&#xa;Normalizes the number (makes it 1 or -1 if not 0)">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_116510710" TEXT="NormalizeRet( )&#xa;Normalizes the number, and returns the magnitude (length)">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_576901080" TEXT="Normal( )&#xa;Returns the norrmal of the number, and does not normalize">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_1320744119" TEXT="Magnitude( )&#xa;Returns the length of the number">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_103406261" TEXT="MagnitudeSquared( )&#xa;Returns the squared length of the number">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_147475335" TEXT="Manhattan( )&#xa;Returns the manhattan length of the number&#xa;(which just happens to be the Magnitude this time)">
<edge WIDTH="thin"/>
</node>
</node>
<node COLOR="#990000" ID="Freemind_Link_1382912537" TEXT="Abs( )&#xa;Returns the absolute value">
<edge WIDTH="thin"/>
</node>
<node COLOR="#990000" ID="Freemind_Link_1234715252" TEXT="Sqrt( )&#xa;Returns the square root">
<edge WIDTH="thin"/>
</node>
</node>
<node ID="Freemind_Link_1137973068" TEXT="Constants">
<edge WIDTH="thin"/>
<node COLOR="#338800" ID="Freemind_Link_676959602" TEXT="Real Zero&#xa;A Number when scaled by this becomes 0&#xa;Also, the value 0">
<edge WIDTH="thin"/>
</node>
<node COLOR="#338800" ID="Freemind_Link_831059199" TEXT="Real Identity&#xa;A Number when scaled by this stays the same">
<edge WIDTH="thin"/>
</node>
<node COLOR="#338800" ID="Freemind_Link_823824768" TEXT="Real One&#xa;The value 1">
<edge WIDTH="thin"/>
</node>
<node COLOR="#338800" ID="Freemind_Link_550468337" TEXT="Real Half&#xa;The value 0.5 or 1/2">
<edge WIDTH="thin"/>
</node>
<node COLOR="#338800" ID="Freemind_Link_1416553435" TEXT="Real Quarter&#xa;The value 0.25 or 1/4">
<edge WIDTH="thin"/>
</node>
<node COLOR="#338800" ID="Freemind_Link_711232080" TEXT="Real SmallestUnit&#xa;The smallest used unit.  Anything less than this should be treated as zero.">
<edge WIDTH="thin"/>
</node>
<node COLOR="#338800" ID="Freemind_Link_800901560" TEXT="Real Pi&#xa;The mathematical value Pi.  3.14...">
<edge WIDTH="thin"/>
</node>
</node>
</node>
</node>
</map>

using System.Collections;
using System.Collections.Generic;
using System.IO;

using UnityEngine;
/*
	USAGE: ADD TO COMPONENT YOU WANT TO EXPORT, PLAY THE SCENE.
	THE SCRIPT WILL PUT ALL FILES TO YOUR <YOUR PROJECT DIRECTORY>\RTMSH_EXPORTS.
	ENJOY!
*/
public class ObjectExport : MonoBehaviour {


    string objectName;
    string path = @".\RTMSH_EXPORTS";
    const string extentionName = ".rtmsh";
    string fileName;
    void Start ()
    {
        Directory.CreateDirectory(path);
        objectName = gameObject.name;
        fileName = objectName + extentionName;
        string vertsString = "";
        string trianglesString = "";

        MeshFilter filter = gameObject.GetComponent<MeshFilter>();
        int[] triangles = filter.mesh.triangles;
        Vector3[] verts = filter.mesh.vertices;

        for (int i = 0; i < triangles.Length; i++)
        {
            string toAppend;
            if (i == triangles.Length - 1)
                toAppend = triangles[i] + ";";
            else
                toAppend = triangles[i] + ",";
            trianglesString += toAppend;
        }
        for (int i = 0; i < verts.Length; i++)
        {
            string toAppend;
            Vector3 currentVert = verts[i];
            if (i == verts.Length - 1)
                toAppend = currentVert.x + "," + currentVert.y + "," + currentVert.z + ";";
            else
                toAppend = currentVert.x + "," + currentVert.y + "," + currentVert.z + ",";
            vertsString += toAppend;
        }

        StreamWriter writer = new StreamWriter(Path.Combine(path,fileName));
        writer.WriteLine("v:" + vertsString);
        writer.WriteLine("t:" + trianglesString);
        writer.Close();

    }

}

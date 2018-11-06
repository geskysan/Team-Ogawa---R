using UnityEngine;
using System.Collections;

public class BackgroundController : MonoBehaviour
{
    [SerializeField]
    float scrollSpeed = 0.2f;

    void Update()
    {
        float scroll = Mathf.Repeat(Time.time * scrollSpeed, 1);
        Vector2 offset = new Vector2(scroll, 0);
        GetComponent<Renderer>().sharedMaterial.SetTextureOffset("_MainTex", offset);
    }
}
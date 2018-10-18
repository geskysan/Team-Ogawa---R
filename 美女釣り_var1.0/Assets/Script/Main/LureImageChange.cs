using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LureImageChange : MonoBehaviour {

    enum LURETUPE
    {
        type1,
        type2,
        type3,
        type4,
        type5,
        type6,
        type7,
        type8,
        type9,
        type10,
        type11,
        type12,
    }

    [SerializeField]
    LURETUPE m_lureType;

    [SerializeField]
    Sprite[] m_lureImage;

    private void Start()
    {
        for (int i = 0; i < m_lureImage.Length; i++)
        {
            if (m_lureType == LURETUPE.type1 + i)
            {
                this.gameObject.GetComponent<Image>().sprite = m_lureImage[i];
            }
        }
    }
}

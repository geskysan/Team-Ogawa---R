using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LureImageChange : MonoBehaviour {

    enum LURETUPE
    {
        cookie,
        money,
        flower,
        cat,
        car,
        ring,
        jewelry,
        wallet,
        lotion,
        perfume,
        Tablet,
        Cake,
    }

    [SerializeField]
    LURETUPE m_lureType;

    [SerializeField]
    Sprite[] m_lureImage;

    private void Start()
    {
        for (int i = 0; i < m_lureImage.Length; i++)
        {
            if (m_lureType == LURETUPE.cookie + i)
            {
                this.gameObject.GetComponent<Image>().sprite = m_lureImage[i];
            }
        }
    }
}

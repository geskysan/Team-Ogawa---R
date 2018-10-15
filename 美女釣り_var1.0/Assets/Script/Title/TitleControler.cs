using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using DG.Tweening;

public class TitleControler : MonoBehaviour {

    [SerializeField]
    GameObject m_tapLogo;

    [SerializeField] float m_scaleSize = 1.2f;
    [SerializeField] float m_scaleTime = 0.7f;

	// Use this for initialization
	void Start () {

        SoundScript.Instance.PlayBGM(SoundNameData.BGM_TITLE);

        m_tapLogo.transform.DOScale(m_scaleSize, m_scaleTime)
            .SetLoops(-1);
	}
	
	// Update is called once per frame
	void Update () {
        if(Input.GetMouseButtonDown(0))
        {
            SceneNavigator.Instance.Change("menu");
        }
	}
}

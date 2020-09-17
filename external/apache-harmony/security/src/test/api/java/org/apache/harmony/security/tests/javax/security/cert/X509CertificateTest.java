/*
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
* @author Alexander Y. Kleymenov
*/

package org.apache.harmony.security.tests.javax.security.cert;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.security.cert.CertificateFactory;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;

import javax.security.cert.CertificateEncodingException;
import javax.security.cert.CertificateException;
import javax.security.cert.CertificateExpiredException;
import javax.security.cert.CertificateNotYetValidException;
import javax.security.cert.X509Certificate;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;



/**
 */

public class X509CertificateTest extends TestCase {

    // Testing data was generated by using of classes
    // from org.apache.harmony.security.asn1 package encoded
    // by org.apache.harmony.misc.Base64 class.

    private static String base64cert =
        "-----BEGIN CERTIFICATE-----\n" +
        "MIIC+jCCAragAwIBAgICAiswDAYHKoZIzjgEAwEBADAdMRswGQYDVQQKExJDZXJ0a" +
        "WZpY2F0ZSBJc3N1ZXIwIhgPMTk3MDAxMTIxMzQ2NDBaGA8xOTcwMDEyNDAzMzMyMF" +
        "owHzEdMBsGA1UEChMUU3ViamVjdCBPcmdhbml6YXRpb24wGTAMBgcqhkjOOAQDAQE" +
        "AAwkAAQIDBAUGBwiBAgCqggIAVaOCAhQwggIQMA8GA1UdDwEB/wQFAwMBqoAwEgYD" +
        "VR0TAQH/BAgwBgEB/wIBBTAUBgNVHSABAf8ECjAIMAYGBFUdIAAwZwYDVR0RAQH/B" +
        "F0wW4EMcmZjQDgyMi5OYW1lggdkTlNOYW1lpBcxFTATBgNVBAoTDE9yZ2FuaXphdG" +
        "lvboYaaHR0cDovL3VuaWZvcm0uUmVzb3VyY2UuSWSHBP///wCIByoDolyDsgMwDAY" +
        "DVR0eAQH/BAIwADAMBgNVHSQBAf8EAjAAMIGZBgNVHSUBAf8EgY4wgYsGBFUdJQAG" +
        "CCsGAQUFBwMBBggrBgEFBQcDAQYIKwYBBQUHAwIGCCsGAQUFBwMDBggrBgEFBQcDB" +
        "AYIKwYBBQUHAwUGCCsGAQUFBwMGBggrBgEFBQcDBwYIKwYBBQUHAwgGCCsGAQUFBw" +
        "MJBggrBgEFBQgCAgYKKwYBBAGCNwoDAwYJYIZIAYb4QgQBMA0GA1UdNgEB/wQDAgE" +
        "BMA4GBCpNhgkBAf8EAwEBATBkBgNVHRIEXTBbgQxyZmNAODIyLk5hbWWCB2ROU05h" +
        "bWWkFzEVMBMGA1UEChMMT3JnYW5pemF0aW9uhhpodHRwOi8vdW5pZm9ybS5SZXNvd" +
        "XJjZS5JZIcE////AIgHKgOiXIOyAzAJBgNVHR8EAjAAMAoGA1UdIwQDAQEBMAoGA1" +
        "UdDgQDAQEBMAoGA1UdIQQDAQEBMAwGByqGSM44BAMBAQADMAAwLQIUAL4QvoazNWP" +
        "7jrj84/GZlhm09DsCFQCBKGKCGbrP64VtUt4JPmLjW1VxQA==\n" +
        "-----END CERTIFICATE-----";

    private java.security.cert.X509Certificate cert;
    private javax.security.cert.X509Certificate tbt_cert;

    protected void setUp() throws Exception {
        try {
            ByteArrayInputStream bais =
                new ByteArrayInputStream(base64cert.getBytes());

            CertificateFactory cf = CertificateFactory.getInstance("X.509");
            this.cert = (java.security.cert.X509Certificate)
                                                cf.generateCertificate(bais);
            this.tbt_cert = X509Certificate.getInstance(cert.getEncoded());
        } catch (java.security.cert.CertificateException e) {
            // The requested certificate type is not available.
            // Test pass..
            this.cert = null;
        } catch (javax.security.cert.CertificateException e) {
            // The requested certificate type is not available.
            // Test pass..
            this.cert = null;
        }
    }

    /**
     * getInstance(InputStream inStream) method testing.
     */
    public void testGetInstance1() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        try {
            ByteArrayInputStream bais =
                new ByteArrayInputStream(cert.getEncoded());

            X509Certificate.getInstance(bais);
        } catch (java.security.cert.CertificateEncodingException e) {
            e.printStackTrace();
            fail("Unexpected CertificateEncodingException was thrown.");
        } catch (CertificateEncodingException e) {
            e.printStackTrace();
            fail("Unexpected CertificateEncodingException was thrown.");
        } catch (CertificateException e) {
            // The requested certificate type is not available.
            // Test pass..
        }

        // Regression for HARMONY-756
        try {
            X509Certificate.getInstance((InputStream) null);
            fail("No expected CertificateException");
        } catch (CertificateException e) {
            //expected;
        }
    }

    /**
     * getInstance(byte[] certData) method testing.
     */
    public void testGetInstance2() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        try {
            X509Certificate.getInstance(cert.getEncoded());
        } catch (java.security.cert.CertificateEncodingException e) {
            e.printStackTrace();
            fail("Unexpected CertificateEncodingException was thrown.");
        } catch (CertificateException e) {
            // The requested certificate type is not available.
            // Test pass..
        }

        // Regression for HARMONY-756
        try {
            X509Certificate.getInstance((byte[]) null);
            fail("No expected CertificateException");
        } catch (CertificateException e) {
            //expected;
        }
    }

    /**
     * checkValidity() method testing.
     */
    public void testCheckValidity1() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        Date date = new Date();
        Date nb_date = tbt_cert.getNotBefore();
        Date na_date = tbt_cert.getNotAfter();
        try {
            tbt_cert.checkValidity();
            assertFalse("CertificateExpiredException expected",
                                            date.compareTo(na_date) > 0);
            assertFalse("CertificateNotYetValidException expected",
                                            date.compareTo(nb_date) < 0);
        } catch (CertificateExpiredException e) {
            assertTrue("Unexpected CertificateExpiredException was thrown",
                                            date.compareTo(na_date) > 0);
        } catch (CertificateNotYetValidException e) {
            assertTrue("Unexpected CertificateNotYetValidException was thrown",
                                            date.compareTo(nb_date) < 0);
        }
    }

    /**
     * checkValidity(Date date) method testing.
     */
    public void testCheckValidity2() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        Date[] date = new Date[4];
        Calendar calendar = Calendar.getInstance();
        for (int i=0; i<date.length; i++) {
            calendar.set(i*50, Calendar.JANUARY, 1);
            date[i] = calendar.getTime();
        }
        Date nb_date = tbt_cert.getNotBefore();
        Date na_date = tbt_cert.getNotAfter();
        for (int i=0; i<date.length; i++) {
            try {
                tbt_cert.checkValidity(date[i]);
                assertFalse("CertificateExpiredException expected",
                                                date[i].compareTo(na_date) > 0);
                assertFalse("CertificateNotYetValidException expected",
                                                date[i].compareTo(nb_date) < 0);
            } catch (CertificateExpiredException e) {
                assertTrue("Unexpected CertificateExpiredException was thrown",
                                                date[i].compareTo(na_date) > 0);
            } catch (CertificateNotYetValidException e) {
                assertTrue("Unexpected CertificateNotYetValidException "
                                + "was thrown", date[i].compareTo(nb_date) < 0);
            }
        }
    }

    /**
     * getVersion() method testing.
     */
    public void testGetVersion() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The version is not correct.",
                                                tbt_cert.getVersion(), 2);
    }

    /**
     * getSerialNumber() method testing.
     */
    public void testGetSerialNumber() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The serial number is not correct.",
                            tbt_cert.getSerialNumber(), cert.getSerialNumber());
    }

    /**
     * getIssuerDN() method testing.
     */
    public void testGetIssuerDN() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The issuer DN is not correct.",
                                    tbt_cert.getIssuerDN(), cert.getIssuerDN());
    }

    /**
     * getSubjectDN() method testing.
     */
    public void testGetSubjectDN() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The subject DN is not correct.",
                                tbt_cert.getSubjectDN(), cert.getSubjectDN());
    }

    /**
     * getNotBefore() method testing.
     */
    public void testGetNotBefore() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The NotBefore date is not correct.",
                                tbt_cert.getNotBefore(), cert.getNotBefore());
    }

    /**
     * getNotAfter() method testing.
     */
    public void testGetNotAfter() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The NotAfter date is not correct.",
                                tbt_cert.getNotAfter(), cert.getNotAfter());
    }

    /**
     * getSigAlgName() method testing.
     */
    public void testGetSigAlgName() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The name of signature algorithm is not correct.",
                                tbt_cert.getSigAlgName(), cert.getSigAlgName());
    }

    /**
     * getSigAlgOID() method testing.
     */
    public void testGetSigAlgOID() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertEquals("The name of OID of signature algorithm is not correct.",
                                tbt_cert.getSigAlgOID(), cert.getSigAlgOID());
    }

    /**
     * getSigAlgParams() method testing.
     */
    public void testGetSigAlgParams() {
        if (this.cert == null) {
            // The requested certificate type is not available.
            // Test can not be applied.
            return;
        }
        assertTrue("The byte array with encoded algorithm parameters "
                + "is not correct.", Arrays.equals(tbt_cert.getSigAlgParams(),
                                                    cert.getSigAlgParams()));
    }

    public static Test suite() {
        return new TestSuite(X509CertificateTest.class);
    }

}

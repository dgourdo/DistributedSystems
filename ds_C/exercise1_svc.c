/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "exercise1.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
ds_ex1_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		Exercise1 inner_product_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case inner_product:
		_xdr_argument = (xdrproc_t) xdr_Exercise1;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) inner_product_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

static void
ds_ex1_2(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		Exercise1 mean_value_2_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case mean_value:
		_xdr_argument = (xdrproc_t) xdr_Exercise1;
		_xdr_result = (xdrproc_t) xdr_double;
		local = (char *(*)(char *, struct svc_req *)) mean_value_2_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

static void
ds_ex1_3(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		Exercise1 product_3_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case product:
		_xdr_argument = (xdrproc_t) xdr_Exercise1;
		_xdr_result = (xdrproc_t) xdr_double;
		local = (char *(*)(char *, struct svc_req *)) product_3_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (DS_Ex1, Ex1_1);
	pmap_unset (DS_Ex1, Ex1_2);
	pmap_unset (DS_Ex1, Ex1_3);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, DS_Ex1, Ex1_1, ds_ex1_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DS_Ex1, Ex1_1, udp).");
		exit(1);
	}
	if (!svc_register(transp, DS_Ex1, Ex1_2, ds_ex1_2, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DS_Ex1, Ex1_2, udp).");
		exit(1);
	}
	if (!svc_register(transp, DS_Ex1, Ex1_3, ds_ex1_3, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DS_Ex1, Ex1_3, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, DS_Ex1, Ex1_1, ds_ex1_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DS_Ex1, Ex1_1, tcp).");
		exit(1);
	}
	if (!svc_register(transp, DS_Ex1, Ex1_2, ds_ex1_2, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DS_Ex1, Ex1_2, tcp).");
		exit(1);
	}
	if (!svc_register(transp, DS_Ex1, Ex1_3, ds_ex1_3, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DS_Ex1, Ex1_3, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}